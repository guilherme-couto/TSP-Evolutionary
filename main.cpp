#include "defines.hpp"
#include "Graph.hpp"
#include "read.hpp"

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
    vector<vector<float>> distance_matrix = readInstanceToMatrix(input_file_address);

    // Print matrix
    cout << "\nDistance matrix:" << endl;
    for (int i = 0; i < distance_matrix.size(); i++)
    {
        for (int j = 0; j < distance_matrix[i].size(); j++)
        {
            cout << distance_matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

