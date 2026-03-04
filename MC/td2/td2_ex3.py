import numpy as np
import matplotlib.pyplot as plt


def function_invers(u):
    if u < 0.5:
        return np.sqrt(2 * u)
    else:
        return 2 - np.sqrt(2 - 2 * u)

def simulation_loi_triangulaire(n):
    u = np.random.rand()
    y = function_invers(u)
    return y

N = 10000

for i in range(N):
    if i == 0:
        echantillon = simulation_loi_triangulaire(N)
    else:
        echantillon = np.append(echantillon, simulation_loi_triangulaire(N))

def densite_theorique(x):
    if 0 <= x < 1:
        return x
    elif 1 <= x <= 2:
        return 2 - x
    else:
        return 0

a,b = 0,2
x_theorique = np.linspace(a, b, 100)
y_theorique = [densite_theorique(x) for x in x_theorique]

plt.figure(figsize=(10, 6))
plt.hist(echantillon, bins=50, density=True, alpha=0.6,label='Simulation (Histogramme)')
plt.plot(x_theorique, y_theorique, 'r-', linewidth=3, label='Densité théorique f(x)')
plt.title(f"Simulation d'une loi triangulaire (N={N}) vs Théorie")
plt.xlabel("y")
plt.ylabel("Densité de probabilité")
plt.legend()
plt.grid(True, alpha=0.3)

plt.show()