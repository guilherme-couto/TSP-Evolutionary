//
// Created by patrick on 16/05/23.
//

#include "ACSAlgorithm.hpp"
#include "defines.hpp"
#include "Structures.hpp"

ACSAlgorithm::ACSAlgorithm(float beta, float rho, float q0, int m, float tau0, int cl, vector<vector<Path>> matrix)
{
    this->beta = beta;
    this->rho = rho;
    this->q0 = q0;
    this->m = m;
    this->tau0 = tau0;
    this->cl = cl;
    this->matrix = matrix;

    this->best_tour.clear();
    this->best_tour_length = 1e8;

    this->number_of_cities = matrix.size();

    // Initialize the number of function evaluations acording to the number of cities
    if (this->number_of_cities < 50)
    {
        this->evaluations_budget = 20000;
    }
    else
    {
        this->evaluations_budget = 70000;
    }
    this->function_evaluations = 0;
}

ACSAlgorithm::~ACSAlgorithm()
{
    this->best_tour.clear();
    this->matrix.clear();
}


double ACSAlgorithm::getBestTourLength()
{
    return this->best_tour_length;
}

void ACSAlgorithm::initializePheromone()
{
    for (int i = 0; i < this->number_of_cities; i++)
    {
        for (int j = 0; j < this->matrix[i].size(); j++)
        {
            this->matrix[i][j].pheromone = this->tau0;
        }
    }
}


double ACSAlgorithm::probabilityToChoosePath(int i, int j, vector<int> J_k_i)
{
    // If j is not in J_k_i, then the probability is 0
    if (find(J_k_i.begin(), J_k_i.end(), j) == J_k_i.end())
    {   
        return 0.0;
    }

    // If j is in J_k_i, then the probability is:
    double numerator = this->matrix[i][j].pheromone * pow(this->matrix[i][j].eta, this->beta);
    double denominator = 0.0;
    for (int u = 0; u < J_k_i.size(); u++)
    {
        denominator += this->matrix[i][J_k_i[u]].pheromone * pow(this->matrix[i][J_k_i[u]].eta, this->beta);
    }
    if (numerator == 0.0 || denominator == 0.0)
    {
        return 0.0;
    }
    return numerator / denominator;
}


int ACSAlgorithm::cityToVisit(int i, vector<int> J_k_i)
{
    int j = -1;
    // Random number between 0 and 1
    float q = (float)rand() / RAND_MAX;

    // If q <= q0, then choose the city with the max pheromone * eta^beta (good exploitation)
    if (q <= q0)
    {
        double max = -1e8;
        int max_index = -1;
        for (int u = 0; u < J_k_i.size(); u++)
        {
            double product = this->matrix[i][J_k_i[u]].pheromone * pow(this->matrix[i][J_k_i[u]].eta, this->beta);
            if (product > max)
            {
                max = product;
                max_index = u;
            }
        }
        j = J_k_i[max_index];
        return j;
    }

    // If q > q0, then choose the city from probability distribution (good exploration)
    else
    {
        // If J_k_i size is 1, then choose the only city
        if (J_k_i.size() == 1)
        {
            j = J_k_i[0];
            return j;
        }
        
        // Compute the probability distribution
        vector<double> probability_distribution;
        double sum = 0.0;
        for (int u = 0; u < J_k_i.size(); u++)
        {   
            double probability = probabilityToChoosePath(i, J_k_i[u], J_k_i);
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
                j = J_k_i[u];
                return j;
            }
        }
    } 
    return j;
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

    // Update the number of function evaluations
    this->function_evaluations++;

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


void ACSAlgorithm::runACS()
{
    // Initialize the pheromone for every path
    this->initializePheromone();

    // Choose a different random city to each ant start the tour
    vector<int> start_cities;
    vector<int> already_chosen_cities;
    vector<vector<int>> tours;

    for (int i = 0; i < this->m; i++)
    {
        int random_city = rand() % this->number_of_cities;
        while (find(already_chosen_cities.begin(), already_chosen_cities.end(), random_city) != already_chosen_cities.end())
        {
            random_city = rand() % this->number_of_cities;
        }
        start_cities.push_back(random_city);
        already_chosen_cities.push_back(random_city);
        vector<int> tour;
        tour.push_back(start_cities[i]);
        tours.push_back(tour);
    }
    
    // Main loop
    while (this->function_evaluations < this->evaluations_budget)
    {
        // For every ant
        for (int k = 0; k < this->m; k++)
        {
            // Reset tour
            tours[k].clear();
            tours[k].push_back(start_cities[k]);

            // Build tour by adding a new city at each step
            while (tours[k].size() < this->number_of_cities)
            {
                // Get distance of the neighbors of the last city in the tour and build the set J_k_i (cities that are not in the tour)
                int i = tours[k][tours[k].size() - 1];
                vector<pair<float, int>> distances_to_i;    // pair -> (distance, city)
                vector<int> J_k_i;                          // set of cities that are not in the tour

                for (int u = 0; u < this->number_of_cities; u++)
                {
                    distances_to_i.push_back(make_pair(matrix[i][u].distance, u));
                    if (find(tours[k].begin(), tours[k].end(), u) == tours[k].end())
                    {
                        J_k_i.push_back(u);
                    }
                }

                // Sort the distances
                sort(distances_to_i.begin(), distances_to_i.end());

                // Build a candidate list with the cl closest cities that are not in the tour
                vector<int> candidate_list;
                candidate_list.clear();
                for (int u = 0; u < this->cl; u++)
                {
                    // Check if the city is not in the tour
                    if (find(tours[k].begin(), tours[k].end(), distances_to_i[u].second) == tours[k].end())
                    {
                        candidate_list.push_back(distances_to_i[u].second);
                    }
                }

                // If exists at least one city in the candidate list, choose one of them
                int j = 1e8;
                if (candidate_list.size() > 0)
                {
                    j = cityToVisit(i, candidate_list);
                    tours[k].push_back(j);
                }
                // Else, choose the closest city in J_k_i
                else
                {
                    for (int u = 0; u < distances_to_i.size(); u++)
                    {
                        if (find(J_k_i.begin(), J_k_i.end(), distances_to_i[u].second) != J_k_i.end())
                        {   
                            j = distances_to_i[u].second;
                            tours[k].push_back(j);
                            break;
                        }
                    }
                }
                
                // Update local pheromone
                localPheromoneUpdate(i, j);
            }
        }

        // Compute the length of each tour
        for (int k = 0; k < this->m; k++)
        {   
            computeLengthOfTour(tours[k]);
        }
        
        // Update global pheromone
        globalPheromoneUpdate();
    }

    // Print the best tour and its length
    cout << "Best tour:";
    for (int i = 0; i < this->best_tour.size(); i++)
    {
        cout << " -> " << this->best_tour[i] + 1;
    }
    cout << " -> " << this->best_tour[0] + 1 << endl;
    cout << "Length: " << this->best_tour_length << endl;
}
