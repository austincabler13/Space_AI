#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // Add this line
#include <random>
#include <chrono>

// Genetic Algorithm Implementation
struct Individual {
    std::vector<int> path;
    double fitness;
};

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, int numGenerations, int numCities) :
        populationSize(populationSize), numGenerations(numGenerations), numCities(numCities) {
        initPopulation();
    }

    void run() {
        for (int gen = 0; gen < numGenerations; ++gen) {
            evaluateFitness();
            selection();
            crossover();
            mutation();
        }
        evaluateFitness();
        printBestIndividual();
    }

private:
    int populationSize;
    int numGenerations;
    int numCities;
    std::vector<Individual> population;
    std::vector<std::vector<double>> distanceMatrix;

    void initPopulation() {
        distanceMatrix = generateDistanceMatrix(numCities);
        std::vector<int> basePath(numCities);
        std::iota(basePath.begin(), basePath.end(), 0);
        for (int i = 0; i < populationSize; ++i) {
            std::shuffle(basePath.begin(), basePath.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
            population.push_back({ basePath, 0.0 });
        }
    }

    std::vector<std::vector<double>> generateDistanceMatrix(int numCities) {
        std::vector<std::vector<double>> matrix(numCities, std::vector<double>(numCities, 0.0));
        for (int i = 0; i < numCities; ++i) {
            for (int j = 0; j < numCities; ++j) {
                if (i != j) {
                    matrix[i][j] = matrix[j][i] = static_cast<double>(rand() % 100 + 1);
                }
            }
        }
        return matrix;
    }

    void evaluateFitness() {
        for (auto& individual : population) {
            individual.fitness = 0.0;
            for (size_t i = 0; i < individual.path.size() - 1; ++i) {
                individual.fitness += distanceMatrix[individual.path[i]][individual.path[i + 1]];
            }
            individual.fitness += distanceMatrix[individual.path.back()][individual.path.front()];
        }
    }

    void selection() {
        std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
            return a.fitness < b.fitness;
        });
        population.resize(populationSize / 2);
    }

    void crossover() {
        std::vector<Individual> newPopulation;
        for (size_t i = 0; i < population.size(); ++i) {
            for (size_t j = i + 1; j < population.size(); ++j) {
                Individual offspring1 = crossoverIndividuals(population[i], population[j]);
                Individual offspring2 = crossoverIndividuals(population[j], population[i]);
                newPopulation.push_back(offspring1);
                newPopulation.push_back(offspring2);
            }
        }
        population = newPopulation;
    }

    Individual crossoverIndividuals(const Individual& parent1, const Individual& parent2) {
        Individual offspring;
        offspring.path.resize(numCities, -1);
        size_t start = rand() % numCities;
        size_t end = rand() % numCities;
        if (start > end) std::swap(start, end);
        for (size_t i = start; i <= end; ++i) {
            offspring.path[i] = parent1.path[i];
        }
        size_t parent2Index = 0;
        for (size_t i = 0; i < numCities; ++i) {
            if (offspring.path[i] == -1) {
                while (std::find(offspring.path.begin(), offspring.path.end(), parent2.path[parent2Index]) != offspring.path.end()) {
                    ++parent2Index;
                }
                offspring.path[i] = parent2.path[parent2Index];
            }
        }
        return offspring;
    }

    void mutation() {
        for (auto& individual : population) {
            if (rand() % 100 < 10) { // 10% mutation rate
                size_t idx1 = rand() % numCities;
                size_t idx2 = rand() % numCities;
                std::swap(individual.path[idx1], individual.path[idx2]);
            }
        }
    }

    void printBestIndividual() {
        auto bestIndividual = std::min_element(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
            return a.fitness < b.fitness;
        });
        std::cout << "Best Path: ";
        for (const auto& city : bestIndividual->path) {
            std::cout << city << " ";
        }
        std::cout << "\nTotal Distance: " << bestIndividual->fitness << "\n";
    }
};

int main() {
    GeneticAlgorithm ga(100, 500, 20); // populationSize, numGenerations, numCities
    ga.run();
    return 0;
}
