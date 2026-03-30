import numpy as np

# Exercice 1 : S3 par Monte Carlo

def generer_geometrique(N, p):
    """X ~ G(p) sur N* : P(X=k) = p*(1-p)^(k-1)"""
    u = np.random.rand(N)
    return (np.log(u) / np.log(1 - p)).astype(int) + 1

N = 1_000_000
p = 1/4  # car 1-p = 3/4

ech = generer_geometrique(N, p)

# S3 = 3 * E[ln(X^4 + 2)]
g = lambda x: 3* np.log(x**4 + 2)

approx_S3 = np.mean(g(ech))
print(f"EX1 :")
print(f"Approximation Monte Carlo de s3 = {approx_S3}")

#comparaison avec la valeur exacte : S3 = 3 * ∑ ln(k^4 + 2) * p * (1-p)^(k-1)
S3_calcul = 0
for k in range(1, 10000):
    S3_calcul += (3/4)**k * np.log(k**4 + 2)
print(f"Autre valeur es de S3 = {S3_calcul}")

# Exercice 2 : Simulation loi de Pareto en utilisant la méthode de l'inversion

# F(x) = 1 - 1/x^3  =>  F^{-1}(u) = (1-u)^{-1/3}
def simuler_pareto(N):
    u = np.random.rand(N)
    return (1 - u) ** (-1/3)   # = u^{-1/3} par symétrie de U[0,1]

pareto_ech = simuler_pareto(N)

# Vérification : E[X] = ∫ x * 3/x^4 dx = 3/2 (théorique)
print(f"\nEX2 :")
print(f"Moyenne empirique  = {np.mean(pareto_ech)}")
print("Variance empirique = ", np.var(pareto_ech))

comparaison = 3/2
print(f"Comparaison avec la valeur théorique de E[X] = {comparaison}")