#include "defines.hpp"
#include "Graph.hpp"
#include "read.hpp"

Graph* read_instances_trstp(string input_file)
{
    Graph* graph_to_return;
    ifstream instance_file;
    instance_file.open(input_file, ios::in);

    string line, garbage;
    stringstream oss;
    string temp;

    int cont = 0;
    int number_of_edges;
    int number_of_nodes;
    int number_of_terminals;

    string source;
    string target;
    string weight;
    string color;
    string id_terminal;
    string garb;

    int j = 0;
    for (size_t i = 0; i < 9; i++)
    {
        getline(instance_file, garbage);
        j++;
    }

    getline(instance_file, line);
    oss << line;

    getline(oss, garbage);

    int pos = garbage.find(' ');

    temp = garbage.substr(pos + 1, garbage.length());

    number_of_nodes = stoi(temp);

    // graph_to_return = make_shared<Graph>();

    for (size_t i = 0; i < number_of_nodes; i++)
    {
        graph_to_return->insert_node(i + 1);
    }

    getline(instance_file, garbage);

    pos = garbage.find(' ');

    temp = garbage.substr(pos + 1, garbage.length());

    number_of_edges = stoi(temp);

    cont = 0;
    while (cont != number_of_edges)
    {
        instance_file >> garb;
        instance_file >> source;
        instance_file >> target;
        instance_file >> weight;
        instance_file >> color;

        graph_to_return->insert_edge(stoi(source), stoi(target), stoi(weight));

        cont++;
    }

    getline(instance_file, garbage);
    getline(instance_file, garbage);
    getline(instance_file, garbage);
    getline(instance_file, garbage);

    getline(instance_file, garbage);

    pos = garbage.find(' ');

    temp = garbage.substr(pos + 1, garbage.length());

    number_of_terminals = stoi(temp);

    cont = 0;

    while (cont != number_of_terminals)
    {
        instance_file >> garb;
        instance_file >> id_terminal;
        cont++;
    }

    return graph_to_return;
}

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


    cout << "Executing " << program_name << " with instance " << input_file_address << " ... " << endl;

    // Read instance
    Graph* g = readInstance(input_file_address);

    return 0;

    g->create_adjacency_matrix();
    //g->print_adjacency_matrix();

    auto start = chrono::high_resolution_clock::now();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    
    cout << "\n\nBest solution after reconnection" << endl;
    // g->get_best_solution()->print();
    cout << "\nDuration: " << duration.count() << " ms" << endl;

    cout << "\n" << endl;

    // cout<<"Graph informations: "<<endl;

    // cout<<"\t Number of nodes: "<<g->order()<<endl;
    // cout<<"\t Number of edges: "<<g->number_of_edges()<<endl;
    // cout<<"\t Is terminal: "<<boolalpha<<g->node_pos(47)->terminal()<<endl;
    // cout<<"\t Source "<<g->node_pos(49)->id()<<" and target "<<g->node_pos(12)->id()<<" has an edge with weight "
    //     <<g->node_pos(49)->edge_for(13)->weight()<<" and color "<<g->node_pos(49)->edge_for(13)->color()<<""<<endl;
    return 0;
}

// ./rstp <path_to_instance> <path_to_result_file> <number_of_tests>