#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "defines.hpp"
#include "Node.hpp"
#include "Solution.hpp"

class Graph
{
public:
    Graph();
    ~Graph();

    int order();
    int number_of_edges();

    Node* first_node();
    Node* last_node();

    void insert_node(int id);
    void insert_edge(int id, int target_id, double weight);
    void set_node_coordinates(int id, double x, double y);

    bool search_node(int id);

    Node* node(int id);
    Node* node_pos(int pos);

    void create_adjacency_matrix();
    void print_adjacency_matrix();

    vector<vector<long int>> get_graph_matrix();

    Solution* get_best_solution();

private:
    int _order;
    int position;
    int _number_of_edges;

    Node* _first_node;
    Node* _last_node;
    Solution* current_solution;
    Solution* best_solution;

    vector<vector<long int>> graph_matrix;
    void increment_graph_order();
};

#endif /* GRAPH_HPP */