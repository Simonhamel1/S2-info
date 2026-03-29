#include <iostream>
#include <vector>
#include <random>
#include <fstream>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);

double simul_loi_uniforme() {
    return dis(gen);
}

int simul_loi_bernoulli(double p) {
    return simul_loi_uniforme() < p ? 1 : -1;
}

std::vector<std::vector<int>> creation_tab(int nmbre_chemin = 10, int nombre_de_lancers = 10, double probabilite = 0.5) {
    std::vector<std::vector<int>> chemin(nmbre_chemin);
    
    for (int trace = 0; trace < nmbre_chemin; trace++) {
        chemin[trace].push_back(simul_loi_bernoulli(probabilite));
        for (int i = 1; i < nombre_de_lancers; i++) {
            chemin[trace].push_back(chemin[trace].back() + simul_loi_bernoulli(probabilite));
        }
    }
    return chemin;
}

int main() {
    auto chemin = creation_tab(1000, 100000, 0.5);
    
    // Export to CSV for visualization
    std::ofstream file("chemin.csv");
    for (int i = 0; i < chemin[0].size(); i++) {
        for (int j = 0; j < chemin.size(); j++) {
            file << chemin[j][i];
            if (j < chemin.size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
    
    std::cout << "Simulation complete. Data saved to chemin.csv\n";
    return 0;
}