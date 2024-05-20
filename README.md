# Traveling Salesman Problem (TSP) Solver

This project provides a comprehensive solution for the Traveling Salesman Problem (TSP) using various algorithms and techniques. It includes implementations for generating random solutions, greedy solutions, and an improved solution using Variable Neighborhood Search (VNS). This project also answers specific questions related to the TSP.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Code Explanation](#code-explanation)
- [Results](#results)
- [Project Questions](#project-questions)


## Features

- **Random Solution Generation**: Generates a random solution for the TSP.
- **Greedy Solution Generation**: Generates a greedy solution for the TSP.
- **Improved Solution**: Utilizes Variable Neighborhood Search (VNS) to improve upon the greedy solution.
- **Solution Evaluation**: Evaluates the total distance of the generated solutions.
- **Save Solutions**: Saves the generated solutions to specified file paths.

## Requirements

- C++ compiler
- [CLion](https://www.jetbrains.com/clion/) (optional, but recommended for development)
- [CMake](https://cmake.org/)

## Installation

**Clone the Repository**
   ```bash
   git clone https://github.com/meryemha/Prog_Avance.git
   cd untitled
   ```
## Code Explanation

### `main.cpp`

This file contains the main function that drives the TSP solver.

- **Input Path**: Prompts the user to enter the path to the TSP file.
- **Generate Solutions**: Creates random and greedy solutions.
- **Save Solutions**: Saves the solutions to files.
- **Evaluate Solutions**: Evaluates the solutions to calculate their total distances.
- **Variable Neighborhood Search**: Improves the greedy solution using VNS and saves the improved solution.
- **Output Results**: Prints the distances of the solutions and their file paths.

### `TSP.h` and `TSP.cpp`

These files contain the TSP class definition and its implementation.

- **Constructor**: Reads the TSP file and initializes the distance matrix.
- **Random Solution**: Generates a random permutation of the cities.
- **Greedy Solution**: Generates a solution using a greedy algorithm.
- **Solution Evaluation**: Calculates the total distance of a given solution.
- **Neighborhood Operations**: Defines various neighborhood operations like 2-opt, exchange, and reinsertion.
- **Variable Neighborhood Search**: Applies VNS to improve a given solution.
- **Save Solution**: Writes a solution to a file.

## Results

The project generates three types of solutions:

1. **Random Solution**: A randomly generated solution, typically with a higher total distance.
2. **Greedy Solution**: A solution generated using a greedy algorithm, generally better than the random solution.
3. **Improved Solution**: An optimized solution obtained by applying Variable Neighborhood Search (VNS) to the greedy solution, typically with the lowest distance among the three.

The solutions are saved to the directory where the TSP file is located, with filenames `random_solution.txt`, `greedy_solution.txt`, and `improved_solution.txt`.

## Project Questions

This project answers the following questions:

1. **How to generate a random solution for TSP?**
    - Implemented in the `generateRandomSolution` method.

2. **How to generate a greedy solution for TSP?**
    - Implemented in the `generateGreedySolution` method.

3. **How to improve a solution using Variable Neighborhood Search?**
    - Implemented in the `variableNeighborhoodSearch` method with neighborhood operations defined in `twoOpt`, `exchange`, and `reinsertion`.

4. **How to evaluate the quality of a solution?**
    - Implemented in the `evaluateSolution` method, which calculates the total distance of the given solution.
