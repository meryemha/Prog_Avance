#include "TSP.h"
#include <iostream>
#include <functional>
#include <filesystem>

// Utilisation de l'espace de noms pour filesystem
namespace fs = std::filesystem;

int main() {
    // Demande du chemin du fichier à l'utilisateur
    std::string filepath;
    std::cout << "Entrez le chemin du fichier france_10.tsp: ";
    std::getline(std::cin, filepath);

    // Création de l'instance TSP avec le fichier donné par l'utilisateur
    TSP tsp(filepath);

    // Extraction du répertoire du fichier d'entrée
    fs::path inputFilePath(filepath);
    fs::path outputDir = inputFilePath.parent_path();

    // Chemins complets pour les fichiers de solution
    fs::path randomSolutionPath = outputDir / "random_solution.txt";
    fs::path greedySolutionPath = outputDir / "greedy_solution.txt";
    fs::path improvedSolutionPath = outputDir / "improved_solution.txt";

    // Génération de solutions
    auto randomSolution = tsp.generateRandomSolution();
    auto greedySolution = tsp.generateGreedySolution();

    // Sauvegarde des solutions générées
    tsp.saveSolution(randomSolutionPath.string(), randomSolution);
    tsp.saveSolution(greedySolutionPath.string(), greedySolution);

    // Évaluation des solutions générées
    double randomScore = tsp.evaluateSolution(randomSolution);
    double greedyScore = tsp.evaluateSolution(greedySolution);

    // Affichage des scores des solutions générées
    std::cout << "Random solution distance: " << randomScore << std::endl;
    std::cout << "Greedy solution distance: " << greedyScore << std::endl;

    // Définition des fonctions de voisinage
    std::vector<std::function<std::vector<int>(const std::vector<int> &, int)>> neighborhoods = {
        [&](const std::vector<int> &s, int i) { return tsp.twoOpt(s, i, (i + 1) % s.size()); },
        [&](const std::vector<int> &s, int i) { return tsp.exchange(s, i, (i + 1) % s.size()); },
        [&](const std::vector<int> &s, int i) { return tsp.reinsertion(s, i, (i + 1) % s.size()); }
    };

    // Recherche locale avec voisinages variables
    auto improvedSolution = tsp.variableNeighborhoodSearch(greedySolution, neighborhoods);
    tsp.saveSolution(improvedSolutionPath.string(), improvedSolution);

    // Évaluation de la solution améliorée
    double improvedScore = tsp.evaluateSolution(improvedSolution);
    std::cout << "Improved solution distance: " << improvedScore << std::endl;

    // Message de confirmation et emplacement des fichiers
    std::cout << "Les fichiers de solution sont aux emplacements suivants:" << std::endl;
    std::cout << "Random solution: " << randomSolutionPath << std::endl;
    std::cout << "Greedy solution: " << greedySolutionPath << std::endl;
    std::cout << "Improved solution: " << improvedSolutionPath << std::endl;

    return 0;
}
