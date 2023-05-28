#include "defines.hpp"
#include "Graph.hpp"
#include "read.hpp"
#include "Structures.hpp"
#include "ACSAlgorithm.hpp"


void outputToFile(string path, string text, bool append) {
    ofstream outputf;

    if (append) {
        outputf.open(path, std::ios_base::app);
    } else {
        outputf.open(path);
    }

    outputf << text;
    outputf.close();
}


int main(int argc, char const *argv[])
{
    // Check command line
    //if (argc != 2)
   // {
    //    cout << "ERROR: Expected: ./<program_name> <input_file_address>" << endl;
        //return 1;
   // }

    //string program_name(argv[0]);
    //string input_file_address(argv[1]);
    //string input_file_address = "../instances/ftv70.atsp";

    //cout << "Executing " << program_name << " with instance " << input_file_address << "\n" << endl;

    // Read instance
    // Graph* g = readInstanceToGraph(input_file_address);
   // vector<vector<Path>> matrix = readInstanceToMatrix(input_file_address);

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

    string files[] = {/*"br17.atsp", "berlin52.tsp",*/"ch130.tsp", "ftv70.atsp"};

    for(int j=0; j<2; j++){
        vector<vector<Path>> matrix = readInstanceToMatrix( "../instances/"+files[j]);
        string output_file_name = "results."+files[j]+".csv";
        outputToFile(output_file_name,"best_tour, time\n", true);



        for (int i = 0; i < 30; i++) {
            srand(i*1561 + j*8785);

            auto beg = chrono::high_resolution_clock::now();

            // Create ACSAlgorithm object (beta, rho, q0, m, tau0, cl, matrix)
            ACSAlgorithm acs = ACSAlgorithm(2.0, 0.1, 0.9, 10, 1.0, 15, matrix);

            // Run ACS
            acs.runACS();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<std::chrono::milliseconds>(end - beg);
            outputToFile(output_file_name, to_string(acs.getBestTourLength()) + ","+ to_string(duration.count()) + "\n", true);
            cout << to_string(duration.count()) << endl;
        }

    }

    /* initialize random seed: */
    /*srand(time(NULL));

    auto beg = chrono::high_resolution_clock::now();

    // Create ACSAlgorithm object (beta, rho, q0, m, tau0, cl, matrix)
    ACSAlgorithm* acs = new ACSAlgorithm(2.0, 0.1, 0.9, 10, 1.0, 15, matrix);

    // Run ACS
    acs->runACS();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::milliseconds>(end - beg);
    //outputToFile("../results/exp2/GRN5-200000-C++_impl-time.csv", to_string(duration.count()) + ",", true);
    cout << to_string(duration.count()) << endl;*/
    return 0;
}

