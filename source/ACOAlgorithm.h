//
// Created by patrick on 16/05/23.
//

#ifndef TSP_EVOLUTIONARY_ACOALGORITHM_H
#define TSP_EVOLUTIONARY_ACOALGORITHM_H


#include "Graph.hpp"

class ACOAlgorithm {
private:
    double beta;
    double rho;
    double q0;
    int m;
    double tau0;
    int cl;
    Graph* graph;
    double** pheromone;

public:
    ACOAlgorithm(double beta, double rho, double q0, int m, double tau0, int cl);
    ~ACOAlgorithm();
    void runACO(int tMax, int seed, Graph* graph);

};


#endif //TSP_EVOLUTIONARY_ACOALGORITHM_H
