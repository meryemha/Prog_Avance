#include "TSP.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <cmath>
#include <numeric>
#include <limits>
#include <iostream>

const double PI = 3.141592;
const double R_TERRE = 6378.137;

TSP::TSP(const std::string &filename) {
    std::ifstream file(filename);
    int n;
    file >> n;
    cities.resize(n);
    for (int i = 0; i < n; ++i) {
        file >> cities[i].name >> cities[i].latitude >> cities[i].longitude;
        cities[i].latitude = toRadians(cities[i].latitude);
        cities[i].longitude = toRadians(cities[i].longitude);
    }
}

void TSP::saveSolution(const std::string &filename, const std::vector<int> &solution) {
    std::ofstream file(filename);
    for (int city : solution) {
        file << city << " ";
    }
    file << std::endl;
}

double TSP::evaluateSolution(const std::vector<int> &solution) {
    double totalDistance = 0.0;
    for (size_t i = 0; i < solution.size() - 1; ++i) {
        totalDistance += distance(cities[solution[i]], cities[solution[i + 1]]);
    }
    totalDistance += distance(cities[solution.back()], cities[solution.front()]);
    return totalDistance;
}

double TSP::toRadians(double degree) {
    return PI * degree / 180.0;
}

double TSP::distance(const City &a, const City &b) {
    return R_TERRE * acos(sin(a.latitude) * sin(b.latitude) +
                          cos(a.latitude) * cos(b.latitude) * cos(b.longitude - a.longitude));
}

std::vector<int> TSP::generateRandomSolution() {
    std::vector<int> solution(cities.size());
    std::iota(solution.begin(), solution.end(), 0);
    std::shuffle(solution.begin(), solution.end(), std::mt19937{std::random_device{}()});
    return solution;
}

std::vector<int> TSP::generateGreedySolution() {
    std::vector<int> solution;
    std::vector<bool> visited(cities.size(), false);
    solution.push_back(0);
    visited[0] = true;

    for (size_t i = 1; i < cities.size(); ++i) {
        int last = solution.back();
        double bestDist = std::numeric_limits<double>::max();
        int bestCity = -1;

        for (size_t j = 0; j < cities.size(); ++j) {
            if (!visited[j]) {
                double d = distance(cities[last], cities[j]);
                if (d < bestDist) {
                    bestDist = d;
                    bestCity = j;
                }
            }
        }

        solution.push_back(bestCity);
        visited[bestCity] = true;
    }

    return solution;
}

std::vector<int> TSP::exchange(const std::vector<int> &solution, int i, int j) {
    std::vector<int> newSolution = solution;
    std::swap(newSolution[i], newSolution[j]);
    return newSolution;
}

std::vector<int> TSP::reinsertion(const std::vector<int> &solution, int i, int j) {
    std::vector<int> newSolution = solution;
    int city = newSolution[i];
    newSolution.erase(newSolution.begin() + i);
    newSolution.insert(newSolution.begin() + j, city);
    return newSolution;
}

std::vector<int> TSP::twoOpt(const std::vector<int> &solution, int i, int j) {
    std::vector<int> newSolution = solution;
    std::reverse(newSolution.begin() + i, newSolution.begin() + j + 1);
    return newSolution;
}

std::vector<int> TSP::bestImprovement(std::vector<int> &solution, std::function<std::vector<int>(const std::vector<int> &, int)> neighborhood) {
    std::vector<int> bestSolution = solution;
    double bestDistance = evaluateSolution(solution);

    for (size_t i = 0; i < solution.size(); ++i) {
        std::vector<int> newSolution = neighborhood(solution, i);
        double newDistance = evaluateSolution(newSolution);

        if (newDistance < bestDistance) {
            bestSolution = newSolution;
            bestDistance = newDistance;
        }
    }

    return bestSolution;
}

std::vector<int> TSP::localSearch(std::vector<int> &solution, std::function<std::vector<int>(const std::vector<int> &, int)> neighborhood) {
    std::vector<int> bestSolution = solution;
    double bestDistance = evaluateSolution(solution);
    bool improved = true;

    while (improved) {
        improved = false;
        for (size_t i = 0; i < solution.size(); ++i) {
            std::vector<int> newSolution = neighborhood(solution, i);
            double newDistance = evaluateSolution(newSolution);

            if (newDistance < bestDistance) {
                bestSolution = newSolution;
                bestDistance = newDistance;
                improved = true;
            }
        }
    }

    return bestSolution;
}

std::vector<int> TSP::variableNeighborhoodSearch(std::vector<int> &solution, const std::vector<std::function<std::vector<int>(const std::vector<int> &, int)>> &neighborhoods) {
    std::vector<int> bestSolution = solution;
    double bestDistance = evaluateSolution(solution);

    for (auto &neighborhood : neighborhoods) {
        std::vector<int> newSolution = localSearch(solution, neighborhood);
        double newDistance = evaluateSolution(newSolution);

        if (newDistance < bestDistance) {
            bestSolution = newSolution;
            bestDistance = newDistance;
        }
    }

    return bestSolution;
}

std::vector<int> TSP::iteratedLocalSearch(std::vector<int> &solution, std::function<std::vector<int>(const std::vector<int> &, int)> neighborhood, int perturbationStrength) {
    std::vector<int> bestSolution = solution;
    double bestDistance = evaluateSolution(solution);
    bool improved = true;

    while (improved) {
        solution = localSearch(solution, neighborhood);
        double currentDistance = evaluateSolution(solution);

        if (currentDistance < bestDistance) {
            bestSolution = solution;
            bestDistance = currentDistance;
        } else {
            improved = false;
        }

        for (int i = 0; i < perturbationStrength; ++i) {
            int idx1 = std::rand() % solution.size();
            int idx2 = std::rand() % solution.size();
            solution = exchange(solution, idx1, idx2);
        }
    }

    return bestSolution;
}
