//
// Created by patrick on 16/05/23.
//

#include "ACOAlgorithm.h"


ACOAlgorithm::ACOAlgorithm(double beta, double rho, double q0, int m, double tau0, int cl) {
    this->beta = beta;
    this->rho = rho;
    this->q0 = q0;
    this->m = m;
    this->tau0 = tau0;
    this->cl = cl;

    this->pheromone = new double * [m];
    for(int i=0; i<m;i++){
        pheromone[i] = new double [m];
    }
}

ACOAlgorithm::~ACOAlgorithm() {

    for(int i=0; i<m;i++){
        delete [] pheromone[i];
    }

   delete [] pheromone;
}


void ACOAlgorithm::runACO(int tMax, int seed, Graph* g) {
    int nEdges = g->number_of_edges();

    for(int i=0; i<nEdges; i++){
        // for each edge, initialize pheromone to tau0
    }

    for(int k=0; k<m; k++){
        //colocar cada formiga k em uma cidade escolhida aleatoriamente
    }

    vector<Edge*> shortestTour; // T+
    double shortestTourLenght; //L+

    //Main loop
    for(int t=0; t<tMax; t++) {
        for (int k = 0; k < m; k++) {//constroi os tours Tk(t)


        }
    }
}