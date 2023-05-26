#include "defines.hpp"
#include "Graph.hpp"
#include "read.hpp"
#include "Structures.hpp"
#include "ACSAlgorithm.hpp"

int main(int argc, char const *argv[])
{
    // Check command line
    if (argc != 2)
    {
        cout << "ERROR: Expected: ./<program_name> <input_file_address>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_address(argv[1]);


    cout << "Executing " << program_name << " with instance " << input_file_address << "\n" << endl;

    // Read instance
    // Graph* g = readInstanceToGraph(input_file_address);
    vector<vector<Path>> matrix = readInstanceToMatrix(input_file_address);

    // return 0;

    // Print matrix
    /* cout << "\nDistance matrix:" << endl;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j].distance << " ";
        }
        cout << endl;
    } */

    /* initialize random seed: */
    srand(time(NULL));

    // Create ACSAlgorithm object (beta, rho, q0, m, tau0, cl, matrix)
    ACSAlgorithm* acs = new ACSAlgorithm(2.0, 0.1, 0.9, 10, 1.0, 15, matrix);

    // Run ACS
    acs->runACS();

    return 0;
}

