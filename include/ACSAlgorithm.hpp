//
// Created by patrick on 16/05/23.
//

#ifndef TSP_EVOLUTIONARY_ACSALGORITHM_HPP
#define TSP_EVOLUTIONARY_ACSALGORITHM_HPP

#include "Structures.hpp"

class ACSAlgorithm {
private:
    float beta;                     // parameter which determines the relative importance of pheromone versus distance
    float rho;                      // pheromone decay parameter (0 < rho < 1)
    float q0;                       // tunable parameter (0 <= q0 <= 1)
    int m;                          // number of ants
    float tau0;                     // initial pheromone value
    int cl;                         // candidate list size
    vector<vector<Path>> matrix;    // matrix with distances, eta and pheromone of each path from i to j

    vector<int> best_tour;          // best tour found so far
    double best_tour_length;        // length of the best tour found so far

    int number_of_cities;           // number of cities
    int evaluations_budget;         // number of function evaluations budget
    int function_evaluations;       // number of function evaluations

public:
    ACSAlgorithm(float beta, float rho, float q0, int m, float tau0, int cl, vector<vector<Path>> matrix);
    ~ACSAlgorithm();
    
    void initializePheromone();
    double probabilityToChoosePath(int i, int j, vector<int> J_k_i);
    int cityToVisit(int i, vector<int> J_k_i);
    void localPheromoneUpdate(int i, int j);
    double computeLengthOfTour(vector<int> tour);
    void globalPheromoneUpdate();
    double getBestTourLength();

    void runACS();
};


#endif //TSP_EVOLUTIONARY_ACSALGORITHM_HPP
