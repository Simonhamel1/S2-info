import numpy as np
import matplotlib.pyplot as plt

N = 10000
K = np.sqrt(2 * np.e / np.pi)

def sim_laplace():
    u = np.random.rand()
    if u < 0.5:
        return np.log(2 * u)
    if u >= 0.5:
        return -np.log(2 * (1 - u))

def f(x):
    return (1 / np.sqrt(2 * np.pi)) * np.exp(-x**2 / 2)

def g(x):
    return 0.5 * np.exp(-abs(x))

exchantillon = []

while len(exchantillon) < N:
    Y = sim_laplace()
    U = np.random.rand()
    if U <= f(Y) / (K * g(Y)):
        exchantillon.append(Y)

exchantillon = np.array(exchantillon)

x = np.linspace(-4, 4, 300)
plt.figure(figsize=(8, 5))
plt.hist(exchantillon, bins=60, density=True, alpha=0.6, color='steelblue', label="Échantillons simulés")
plt.plot(x, f(x), label="N(0,1) théorique")
plt.legend()
plt.tight_layout()
plt.show()