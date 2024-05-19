#ifndef TSP_H
#define TSP_H

#include "City.h"
#include <vector>
#include <string>
#include <functional>

class TSP {
public:
    TSP(const std::string &filename);
    void saveSolution(const std::string &filename, const std::vector<int> &solution);
    double evaluateSolution(const std::vector<int> &solution);
    std::vector<int> generateRandomSolution();
    std::vector<int> generateGreedySolution();
    std::vector<int> twoOpt(const std::vector<int> &solution, int i, int j);
    std::vector<int> exchange(const std::vector<int> &solution, int i, int j);
    std::vector<int> reinsertion(const std::vector<int> &solution, int i, int j);
    std::vector<int> bestImprovement(std::vector<int> &solution, std::function<std::vector<int>(const std::vector<int> &, int)> neighborhood);
    std::vector<int> localSearch(std::vector<int> &solution, std::function<std::vector<int>(const std::vector<int> &, int)> neighborhood);
    std::vector<int> variableNeighborhoodSearch(std::vector<int> &solution, const std::vector<std::function<std::vector<int>(const std::vector<int> &, int)>> &neighborhoods);
    std::vector<int> iteratedLocalSearch(std::vector<int> &solution, std::function<std::vector<int>(const std::vector<int> &, int)> neighborhood, int perturbationStrength);
private:
    std::vector<City> cities;
    double toRadians(double degree);
    double distance(const City &a, const City &b);
};

#endif // TSP_H
