//
// Created by patrick on 16/05/23.
//

#include "ACSAlgorithm.hpp"
#include "defines.hpp"
#include "Structures.hpp"

ACSAlgorithm::ACSAlgorithm(float beta, float rho, float q0, int m, float tau0, int cl)
{
    this->beta = beta;
    this->rho = rho;
    this->q0 = q0;
    this->m = m;
    this->tau0 = tau0;
    this->cl = cl;

    this->best_tour.clear();
    this->best_tour_length = 1e8;
}

ACSAlgorithm::~ACSAlgorithm() {}


void ACSAlgorithm::initializePheromone()
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j].pheromone = this->tau0;
        }
    }
}


double ACSAlgorithm::probabilityToChoosePath(int k, int i, int j, vector<int> J_k_i)
{
    // If s is not in J_k_i, then the probability is 0
    if (find(J_k_i.begin(), J_k_i.end(), j) == J_k_i.end())
    {
        return 0.0;
    }

    // If s is in J_k_i, then the probability is:
    double numerator = matrix[i][j].pheromone * pow(matrix[i][j].eta, this->beta);
    double denominator = 0.0;
    for (int u = 0; u < J_k_i.size(); u++)
    {
        denominator += matrix[i][J_k_i[u]].pheromone * pow(matrix[i][J_k_i[u]].eta, this->beta);
    }

    return numerator / denominator;
}


int ACSAlgorithm::cityToVisit(int k, int i, vector<int> J_k_i)
{
    // Random number between 0 and 1
    float q = (float)rand() / RAND_MAX;

    // If q <= q0, then choose the city with the max pheromone * eta^beta (good exploitation)
    if (q <= q0)
    {
        double max = -1e8;
        int max_index = -1;
        for (int u = 0; u < J_k_i.size(); u++)
        {
            double product = matrix[i][J_k_i[u]].pheromone * pow(matrix[i][J_k_i[u]].eta, this->beta);
            if (product > max)
            {
                max = product;
                max_index = u;
            }
        }
        return J_k_i[max_index];
    }

    // If q > q0, then choose the city from probability distribution (good exploration)
    else
    {
        // Compute the probability distribution
        vector<double> probability_distribution;
        double sum = 0.0;
        for (int u = 0; u < J_k_i.size(); u++)
        {
            double probability = probabilityToChoosePath(k, i, J_k_i[u], J_k_i);
            probability_distribution.push_back(probability);
            sum += probability;
        }

        // Choose from a roulette wheel
        double random_number = (float)rand() / RAND_MAX;
        double partial_sum = 0.0;
        for (int u = 0; u < J_k_i.size(); u++)
        {
            partial_sum += probability_distribution[u] / sum;
            if (random_number <= partial_sum)
            {
                return J_k_i[u];
            }
        }
    }
}


void ACSAlgorithm::localPheromoneUpdate(int i, int j)
{
    matrix[i][j].pheromone = (1 - this->rho) * matrix[i][j].pheromone + this->rho * this->tau0;
}


double ACSAlgorithm::computeLengthOfTour(vector<int> tour)
{
    double length = 0.0;
    for (int i = 0; i < tour.size() - 1; i++)
    {
        length += matrix[tour[i]][tour[i + 1]].distance;
    }
    length += matrix[tour[tour.size() - 1]][tour[0]].distance;

    // Check if length is smaller than best_tour_length
    if (length < this->best_tour_length)
    {
        this->best_tour = tour;
        this->best_tour_length = length;
    }

    return length;
}


void ACSAlgorithm::globalPheromoneUpdate()
{
    double delta_tau = 1.0 / this->best_tour_length;
    for (int i = 0; i < this->best_tour.size() - 1; i++)
    {
        matrix[this->best_tour[i]][this->best_tour[i + 1]].pheromone = (1 - this->rho) * matrix[this->best_tour[i]][this->best_tour[i + 1]].pheromone + this->rho * delta_tau;
    }
    matrix[this->best_tour[this->best_tour.size() - 1]][this->best_tour[0]].pheromone = (1 - this->rho) * matrix[this->best_tour[this->best_tour.size() - 1]][this->best_tour[0]].pheromone + this->rho * delta_tau;
}
