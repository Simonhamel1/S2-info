"""
Nappe de volatilité implicite BTC — Deribit via ccxt
Version corrigée : filtrage strict, surface lisse
-----------------------------------------------------
pip install ccxt pandas numpy scipy matplotlib seaborn
python vol_surface_v2.py
"""

import ccxt
import pandas as pd
import numpy as np
from scipy.interpolate import RectBivariateSpline
from scipy.stats import pearsonr, spearmanr
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import seaborn as sns
import warnings
warnings.filterwarnings("ignore")

# ─────────────────────────────────────────
# 1. FETCH DERIBIT
# ─────────────────────────────────────────

def fetch_vol_surface(underlying="BTC"):
    exchange = ccxt.deribit()
    exchange.load_markets()

    rows = []
    for symbol, market in exchange.markets.items():
        if not (market["type"] == "option" and market["base"] == underlying):
            continue
        try:
            ticker = exchange.fetch_ticker(symbol)
            info   = ticker.get("info", {})

            iv          = float(info.get("mark_iv") or 0)
            strike      = float(market["strike"])
            expiry      = pd.to_datetime(market["expiryDatetime"])
            option_type = market["optionType"]
            spot        = float(info.get("underlying_price") or 0)
            bid_iv      = float(info.get("bid_iv") or 0)
            ask_iv      = float(info.get("ask_iv") or 0)
            oi          = float(info.get("open_interest") or 0)
            volume      = float(ticker.get("quoteVolume") or 0)
            delta       = float((info.get("greeks") or {}).get("delta") or 0)
            vega        = float((info.get("greeks") or {}).get("vega") or 0)

            if iv <= 0 or spot <= 0:
                continue

            now      = pd.Timestamp.utcnow().tz_localize(None)
            tte_days = max((expiry.tz_localize(None) - now).days, 0)
            moneyness = np.log(strike / spot)

            rows.append({
                "symbol":       symbol,
                "expiry":       expiry.date(),
                "tte_days":     tte_days,
                "strike":       strike,
                "spot":         spot,
                "moneyness":    round(moneyness, 4),
                "option_type":  option_type,
                "iv":           round(iv, 4),
                "bid_iv":       round(bid_iv, 4),
                "ask_iv":       round(ask_iv, 4),
                "iv_spread":    round(ask_iv - bid_iv, 4),
                "open_interest": oi,
                "volume":       volume,
                "delta":        delta,
                "vega":         vega,
            })
        except Exception:
            continue

    return pd.DataFrame(rows)


# ─────────────────────────────────────────
# 2. NETTOYAGE STRICT
# ─────────────────────────────────────────

print("Connexion Deribit…")
df_raw = fetch_vol_surface("BTC")
print(f"  Raw : {len(df_raw)} options")

df = df_raw.copy()

# Filtres stricts
df = df[
    (df["tte_days"] >= 1) &
    (df["tte_days"] <= 180) &           # max 6 mois — au-delà trop sparse
    (df["moneyness"].between(-0.4, 0.4)) &  # ±40% moneyness seulement
    (df["iv"] >= 20) &                  # IV min réaliste pour BTC
    (df["iv"] <= 150) &                 # IV max — coupe les deep OTM aberrants
    (df["iv_spread"] < 30) &            # spread trop large = option illiquide
    (df["open_interest"] > 0)           # doit avoir de l'OI
].copy()

# Supprimer les outliers IV par maturité (IQR)
def remove_iv_outliers(group):
    q1, q3 = group["iv"].quantile(0.10), group["iv"].quantile(0.90)
    iqr = q3 - q1
    return group[(group["iv"] >= q1 - 1.5*iqr) & (group["iv"] <= q3 + 1.5*iqr)]

df = df.groupby("expiry", group_keys=False).apply(remove_iv_outliers)

print(f"  Après filtrage : {len(df)} options\n")
df.to_csv("vol_surface_clean.csv", index=False)


# ─────────────────────────────────────────
# 3. NAPPE DE VOL — SURFACE LISSE
# ─────────────────────────────────────────

def plot_vol_surface(df):
    # Grille régulière pour interpolation
    money_grid = np.linspace(-0.35, 0.35, 50)
    tte_grid   = np.linspace(df["tte_days"].min(), df["tte_days"].max(), 50)

    # Pivot : moyenne IV par cellule (moneyness arrondi × maturité)
    df["m_bin"] = pd.cut(df["moneyness"], bins=25, labels=False)
    df["t_bin"] = pd.cut(df["tte_days"],  bins=25, labels=False)

    pivot = df.groupby(["t_bin", "m_bin"])["iv"].median().unstack()
    pivot = pivot.interpolate(axis=0, limit_direction="both")
    pivot = pivot.interpolate(axis=1, limit_direction="both")
    pivot = pivot.fillna(method="ffill").fillna(method="bfill")

    # Lissage gaussien léger
    from scipy.ndimage import gaussian_filter
    Z_smooth = gaussian_filter(pivot.values.astype(float), sigma=1.2)

    # Grilles pour le plot
    T_vals = np.linspace(df["tte_days"].min(), df["tte_days"].max(), Z_smooth.shape[0])
    M_vals = np.linspace(-0.35, 0.35, Z_smooth.shape[1])
    M_grid, T_grid = np.meshgrid(M_vals, T_vals)

    fig = plt.figure(figsize=(13, 8))
    ax  = fig.add_subplot(111, projection="3d")

    surf = ax.plot_surface(
        M_grid, T_grid, Z_smooth,
        cmap="RdYlGn_r", alpha=0.9,
        edgecolor="none", rstride=1, cstride=1
    )

    # Contour projeté sur le sol
    ax.contourf(M_grid, T_grid, Z_smooth, zdir="z",
                offset=Z_smooth.min() - 2, cmap="RdYlGn_r", alpha=0.3, levels=12)

    ax.set_xlabel("Log-Moneyness  ln(K/S)", labelpad=12, fontsize=10)
    ax.set_ylabel("Maturité (jours)",        labelpad=12, fontsize=10)
    ax.set_zlabel("IV (%)",                  labelpad=8,  fontsize=10)
    ax.set_title("Nappe de Volatilité Implicite — BTC Options (Deribit)",
                 fontsize=13, pad=20)

    cbar = fig.colorbar(surf, ax=ax, shrink=0.45, pad=0.1)
    cbar.set_label("IV (%)", fontsize=9)

    # Angle de vue propre
    ax.view_init(elev=28, azim=-60)
    ax.set_box_aspect([1.2, 1.2, 0.8])

    plt.tight_layout()
    plt.savefig("vol_surface_3d.png", dpi=150, bbox_inches="tight")
    plt.close()
    print("Nappe sauvegardée : vol_surface_3d.png")

plot_vol_surface(df)


# ─────────────────────────────────────────
# 4. CORRÉLATIONS
# ─────────────────────────────────────────

vars_corr = {
    "iv":            "IV (%)",
    "moneyness":     "Log-Moneyness",
    "tte_days":      "Maturité (j)",
    "open_interest": "Open Interest",
    "volume":        "Volume",
    "iv_spread":     "Spread IV",
    "vega":          "Vega",
    "delta":         "Delta (abs)",
}

df["delta"] = df["delta"].abs()
corr_df = df[list(vars_corr.keys())].dropna()

# ── Heatmap ──
fig, axes = plt.subplots(1, 2, figsize=(18, 7))
for ax, method, title in zip(
    axes,
    ["pearson", "spearman"],
    ["Pearson (linéaire)", "Spearman (rang)"]
):
    mat = corr_df.corr(method=method).rename(columns=vars_corr, index=vars_corr)
    mask = np.triu(np.ones_like(mat, dtype=bool), k=1)
    sns.heatmap(mat, ax=ax, mask=mask, cmap="RdBu_r", center=0,
                vmin=-1, vmax=1, annot=True, fmt=".2f",
                linewidths=0.5, cbar_kws={"shrink": 0.8})
    ax.set_title(title, fontsize=12, pad=10)
    ax.tick_params(axis="x", rotation=30)
    ax.tick_params(axis="y", rotation=0)

plt.suptitle("Corrélations — Vol Surface BTC Deribit", fontsize=13, y=1.01)
plt.tight_layout()
plt.savefig("correlations_heatmap.png", dpi=150, bbox_inches="tight")
plt.close()
print("Heatmap sauvegardée : correlations_heatmap.png")

# ── Scatterplots ──
pairs = [
    ("moneyness",    "iv",            "Skew : Moneyness vs IV"),
    ("tte_days",     "iv",            "Term structure : Maturité vs IV"),
    ("open_interest","iv",            "Open Interest vs IV"),
    ("volume",       "iv",            "Volume vs IV"),
    ("iv_spread",    "iv",            "Liquidité (spread) vs IV"),
    ("tte_days",     "open_interest", "Maturité vs Open Interest"),
]

fig, axes = plt.subplots(2, 3, figsize=(16, 10))
for ax, (xv, yv, title) in zip(axes.flatten(), pairs):
    sub = corr_df[[xv, yv]].dropna()
    r_p, p_p = pearsonr(sub[xv], sub[yv])
    r_s, p_s = spearmanr(sub[xv], sub[yv])

    ax.scatter(sub[xv], sub[yv], alpha=0.3, s=10, color="steelblue")
    z = np.polyfit(sub[xv], sub[yv], 1)
    xl = np.linspace(sub[xv].min(), sub[xv].max(), 100)
    ax.plot(xl, np.polyval(z, xl), "r-", lw=1.8)

    ax.set_xlabel(vars_corr.get(xv, xv), fontsize=9)
    ax.set_ylabel(vars_corr.get(yv, yv), fontsize=9)
    ax.set_title(title, fontsize=10)
    sig = "✓" if p_p < 0.05 else "✗"
    ax.text(0.04, 0.93,
            f"r={r_p:.2f}  p={p_p:.3f} {sig}\nρ={r_s:.2f}  p={p_s:.3f}",
            transform=ax.transAxes, fontsize=8, va="top",
            bbox=dict(boxstyle="round", fc="white", alpha=0.75))

plt.suptitle("Scatterplots — Vol Surface BTC Deribit", fontsize=13)
plt.tight_layout()
plt.savefig("correlations_scatter.png", dpi=150, bbox_inches="tight")
plt.close()
print("Scatter sauvegardé : correlations_scatter.png")

# ── Tableau résultats ──
results = []
for var in ["moneyness","tte_days","open_interest","volume","iv_spread","vega","delta"]:
    sub = corr_df[["iv", var]].dropna()
    r_p, p_p = pearsonr(sub["iv"], sub[var])
    r_s, p_s = spearmanr(sub["iv"], sub[var])
    results.append({
        "Variable":   vars_corr[var],
        "Pearson r":  round(r_p, 3),
        "p-val (P)":  round(p_p, 4),
        "Spearman ρ": round(r_s, 3),
        "p-val (S)":  round(p_s, 4),
        "Sig. 5%":    "✓" if p_p < 0.05 else "✗",
    })

res_df = pd.DataFrame(results)
res_df.to_csv("correlation_results.csv", index=False)
print("\n── Résultats ──")
print(res_df.to_string(index=False))
print("\nTerminé ✓")