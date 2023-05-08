#ifndef READ_HPP
#define READ_HPP

#include "defines.hpp"
#include "Graph.hpp"

Graph* readInstance(string input_file_address)
{
    // Get input file name
    string input_file;
    size_t pos = input_file_address.find_last_of('/');
    if (pos != string::npos)
    {
        input_file = input_file_address.substr(pos + 1, input_file_address.length());
    }
    else
    {
        input_file = input_file_address;
    }

    // Error handling
    if (input_file != "bayg29.tsp" && input_file != "ch130.tsp" && input_file != "br17.atsp" && input_file != "ftv70.atsp")
    {
        cout << "Error: Invalid input file address(" << input_file_address << ")" << endl;
        cout << "Valid input files are: bayg29.tsp, ch130.tsp, br17.atsp, ftv70.atsp" << endl;
        exit(1);
    }

    // Create empty graph and open file
    Graph* graph = new Graph();
    ifstream instance_file;
    instance_file.open(input_file_address, ios::in);

    // Read file
    string line, garbage;
    stringstream ss;
    string temp;

    int cont = 0, j;
    int number_of_edges;
    int number_of_nodes;

    string source;
    string target;
    string distance;
    string x_coord;
    string y_coord;

    if (input_file == "bayg29.tsp")
    {
        // Skip first 3 lines
        for (int i = 0; i < 3; i++)
        {
            getline(instance_file, garbage);
        }

        // Get number of nodes
        getline(instance_file, line);
        ss << line;
        getline(ss, garbage);
        pos = garbage.find(' ');
        temp = garbage.substr(pos + 1, garbage.length());
        number_of_nodes = stoi(temp);
        cout << "Number of nodes: " << number_of_nodes << endl;

        // Insert nodes
        for (int i = 0; i < number_of_nodes; i++)
        {
            graph->insert_node(i + 1);
        }

        // Skip 4 lines
        for (int i = 0; i < 4; i++)
        {
            getline(instance_file, garbage);
        }

        // Get edges from superior triangular matrix
        for (int i = 1; i <= number_of_nodes; i++)
        {
            getline(instance_file, line);
            stringstream aux_ss(line);
            
            for (int j = i+1; j <= number_of_nodes; j++)
            {
                aux_ss >> distance;
                if (distance != " ")
                {
                    graph->insert_edge(i, j, stod(distance));
                    graph->insert_edge(j, i, stod(distance));
                }
                else
                {
                    cout << "No edge from " << i << " to " << j << endl;
                }
            }
        }
        
    }
    else if (input_file == "ch130.tsp")
    {
        // Skip first 3 lines
        for (int i = 0; i < 3; i++)
        {
            getline(instance_file, garbage);
        }

        // Get number of nodes
        getline(instance_file, line);
        ss << line;
        getline(ss, garbage);
        pos = garbage.find(' ');
        temp = garbage.substr(pos + 1, garbage.length());
        number_of_nodes = stoi(temp);
        cout << "Number of nodes: " << number_of_nodes << endl;

        // Insert nodes
        for (int i = 0; i < number_of_nodes; i++)
        {
            graph->insert_node(i + 1);
        }

        // Skip 2 lines
        for (int i = 0; i < 2; i++)
        {
            getline(instance_file, garbage);
        }

        // Get nodes coordinates
        for (int i = 0; i < number_of_nodes; i++)
        {
            string node_id;
            getline(instance_file, line);
            stringstream aux_ss(line);
            aux_ss >> node_id;
            aux_ss >> x_coord;
            aux_ss >> y_coord;
            
            graph->set_node_coordinates(stoi(node_id), stod(x_coord), stod(y_coord));
        }

        // Set edges between nodes
        for (int i = 1; i <= number_of_nodes; i++)
        {
            double x1, y1;
            x1 = graph->node(i)->x_coordinate();
            y1 = graph->node(i)->y_coordinate();

            for (int j = i+1; j <= number_of_nodes; j++)
            {
                double x2, y2;
                double euclidean_distance;

                x2 = graph->node(j)->x_coordinate();
                y2 = graph->node(j)->y_coordinate();

                // Weight = Euclidean distance
                euclidean_distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);

                graph->insert_edge(i, j, euclidean_distance);
                graph->insert_edge(j, i, euclidean_distance);
            }
        }

    }
    else if (input_file == "br17.atsp")
    {
        // Skip first 3 lines
        for (int i = 0; i < 3; i++)
        {
            getline(instance_file, garbage);
        }

        // Get number of nodes
        getline(instance_file, line);
        ss << line;
        getline(ss, garbage);
        pos = garbage.find(' ');
        temp = garbage.substr(pos + 1, garbage.length());
        number_of_nodes = stoi(temp);
        cout << "Number of nodes: " << number_of_nodes << endl;

        // Insert nodes
        for (int i = 0; i < number_of_nodes; i++)
        {
            graph->insert_node(i + 1);
        }

        // Skip 3 lines
        for (int i = 0; i < 3; i++)
        {
            getline(instance_file, garbage);
        }

        // Get edges from matrix
        for (int i = 1; i <= number_of_nodes; i++)
        {
            getline(instance_file, line);
            stringstream aux_ss(line);
            
            for (int j = 1; j <= number_of_nodes; j++)
            {
                aux_ss >> distance;
                if (distance != " ")
                {
                    graph->insert_edge(i, j, stod(distance));
                }
                else
                {
                    cout << "No edge from " << i << " to " << j << endl;
                }
            }
        }
    }
    else if (input_file == "ftv70.atsp")
    {

    }

    cout << "File read and graph created" << endl;
    return graph;
}

#endif // READ_HPP