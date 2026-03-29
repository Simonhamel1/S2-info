import math
import numpy as np
import matplotlib.pyplot as plt

def tcl_uniforme_normal(N, n_tcl, a, b, delta):
    
    
    echantillon = []
    AI = []
    theo = []
    empirique = []

    for i in range(N):
        somme = 0
        for j in range(n_tcl):
          u=np.random.random()
          somme += u

        z = (somme - n_tcl * 0.5) / math.sqrt(n_tcl / 12)
        echantillon.append(z)

    
    ai = a
    while ai < b:
        f_theo = (1 / math.sqrt(2 * math.pi)) * math.exp(-0.5 * ai**2)
        ni = 0
        bi = ai + delta
        for valeur in echantillon:
            if valeur >= ai and valeur < bi:
                ni += 1

        f_emp = ni / (N * delta)

        AI.append(ai)
        theo.append(f_theo)
        empirique.append(f_emp)

        ai = ai + delta

 
    plt.plot(AI, theo)
    plt.scatter(AI, empirique)
    plt.title("TCL avec uniforme")
    plt.show()

def tcl_exponentielle_nomal(N, n_tcl, theta, a, b, delta):
    echantillon = []
    AI = []
    theo = []
    empirique = []

    for _ in range(N):
        somme = 0
        for _ in range(n_tcl):
            u = np.random.random()
            x = -theta * math.log(1 - u)  # Génération d'une exponentielle
            somme += x

        # Normalisation pour TCL : (moyenne - espérance) / écart-type
        z = (somme / n_tcl - theta) / (theta / math.sqrt(n_tcl))
        echantillon.append(z)

    
    ai = a
    while ai < b:
        # Densité théorique d'une loi NORMALE N(0,1) car TCL
        f_theo = (1 / math.sqrt(2 * math.pi)) * math.exp(-0.5 * ai**2)
        ni = 0
        bi = ai + delta
        for valeur in echantillon:
            if valeur >= ai and valeur < bi:
                ni += 1

        f_emp = ni / (N * delta)

        AI.append(ai)
        theo.append(f_theo)
        empirique.append(f_emp)

        ai = ai + delta

 
    plt.plot(AI, theo)
    plt.scatter(AI, empirique)
    plt.title("TCL avec exponentielle")
    plt.show()

def box_muller(N, a, b, delta):
    echantillon = []
    AI = []
    theo = []
    empirique = []

    for i in range(N):
        u1 = np.random.random()
        u2 = np.random.random()
        z0 = math.sqrt(-2.0 * math.log(u1)) * math.cos(2.0 * math.pi * u2)
        echantillon.append(z0)

    ai = a
    while ai < b:
        f_theo = (1 / math.sqrt(2 * math.pi)) * math.exp(-0.5 * ai**2)
        ni = 0
        bi = ai + delta
        for valeur in echantillon:
            if valeur >= ai and valeur < bi:
                ni += 1

        f_emp = ni / (N * delta)

        AI.append(ai)
        theo.append(f_theo)
        empirique.append(f_emp)

        ai = ai + delta

 
    plt.plot(AI, theo)
    plt.scatter(AI, empirique)
    plt.title("Box-Muller")
    plt.show()
    
    
def normale_non_standard(N, mu, sigma, a, b, delta):
    echantillon = []
    AI = []
    theo = []
    empirique = []

    n_tcl = 100
    for _ in range(N):
        somme = 0
        for _ in range(n_tcl):
            u = np.random.random()
            somme += u

        z = (somme - n_tcl * 0.5) / math.sqrt(n_tcl / 12)
        x = mu + sigma * z
        echantillon.append(x)

    ai = a
    while ai < b:
        f_theo = (1 / (sigma * math.sqrt(2 * math.pi))) * math.exp(-0.5 * ((ai - mu) / sigma)**2)
        ni = 0
        bi = ai + delta
        for valeur in echantillon:
            if valeur >= ai and valeur < bi:
                ni += 1

        f_emp = ni / (N * delta)

        AI.append(ai)
        theo.append(f_theo)
        empirique.append(f_emp)

        ai = ai + delta

    plt.plot(AI, theo)
    plt.scatter(AI, empirique)
    plt.title("Normale non standard")
    plt.show()


tcl_uniforme_normal(N=10000, n_tcl=100, a=-3, b=3, delta=0.06)
tcl_exponentielle_nomal(N=10000, n_tcl=100, theta=1, a=-3, b=3, delta=0.06) # exo 4 question 2
box_muller(N=10000, a=-3, b=3, delta=0.06) # exo 4 question 3
normale_non_standard(N=10000, mu=5, sigma=2, a=-2, b=12, delta=0.1)
