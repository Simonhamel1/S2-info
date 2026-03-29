import random
import math
from scipy import integrate

random.seed(42)

def generer_uniforme():
    return random.random()

def generer_exponentielle(lam):
    """Methode d'inversion : Y = -ln(1-U) / lambda"""
    u = random.random()
    return -math.log(1 - u) / lam

def estimer_I1(n):
    total = 0.0
    for _ in range(n):
        u = generer_uniforme()
        total += math.tan(math.log(1 + u))
    return total / n

def estimer_I3(n):
    total = 0.0
    for _ in range(n):
        y = generer_exponentielle(3)
        total += math.log(3 + math.sin(y ** 2))
    return total / (3 * n)


# VRAIE_I1 = 0.42527
# VRAIE_I3 = 0.38257

VRAIE_I1, error = integrate.quad(lambda x: math.tan(math.log(1+x)), 0, 1)

VRAIE_I3, error = integrate.quad(lambda x: math.log(3 + math.sin(x**2)) * math.exp(-3*x), 0, math.inf)


n = 100000
est_i1 = estimer_I1(n)
est_i3 = estimer_I3(n)
err_i1 = abs(est_i1 - VRAIE_I1) / VRAIE_I1 * 100
err_i3 = abs(est_i3 - VRAIE_I3) / VRAIE_I3 * 100

print(f"  I1 : estime = {est_i1}  |  vrai ~ {VRAIE_I1}  |  erreur = {err_i1}%")
print(f"  I3 : estime = {est_i3}  |  vrai ~ {VRAIE_I3}  |  erreur = {err_i3}%")