#include "Graph.hpp"
#include "random/Xoshiro256plus.h"

Graph::Graph()
{
    this->_order = 0;
    this->position = 0;
    this->_number_of_edges = 0;
    this->_first_node = nullptr;
    this->_last_node = nullptr;
}

Graph::~Graph()
{
    // delete automático
    // a não ser que aloquemos alguma outra coisa na construção
}

int Graph::order()
{
    return this->_order;
}

int Graph::number_of_edges()
{
    return this->_number_of_edges;
}

Node* Graph::first_node()
{
    return this->_first_node;
}

Node* Graph::last_node()
{
    return this->_last_node;
}

void Graph::insert_node(int id)
{
    if (this->first_node() == nullptr)
    {
        Node* node(new Node(id));
        this->_first_node = this->_last_node = node;
        node->set_position(this->position);
    }
    else
    {
        if (!this->search_node(id))
        {
            Node* node(new Node(id));
            this->last_node()->set_next_node(node);
            this->_last_node = node;
            node->set_position(this->position);
        }
        else
        {
            return;
        }
    }
    this->position += 1;
    this->increment_graph_order();
}

void Graph::insert_edge(int id, int target_id, double weight)
{
    Node* node, *target_node;

    node = this->node(id);
    target_node = this->node(target_id);

    // If edge doesn't exist, insert
    if (!node->has_edge_for(target_id))
    {
        this->_number_of_edges++;

        node->insert_edge(target_id, target_node->position(), weight);

        node->increment_out_degree();
        target_node->increment_in_degree();
        node->increment_degree();
        target_node->increment_degree();
    }
}

bool Graph::search_node(int id)
{
    Node* node = this->node(id);

    if (node == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Node* Graph::node(int id)
{
    Node* helper = this->_first_node;

    while (helper != nullptr)
    {
        if (helper->id() == id)
        {
            return helper;
        }
        else
        {
            helper = helper->next_node();
        }
    }

    return nullptr;
}

Node* Graph::node_pos(int pos)
{
    Node* helper = this->_first_node;

    while (helper != nullptr)
    {
        if (helper->position() == pos)
        {
            return helper;
        }
        else
        {
            helper = helper->next_node();
        }
    }

    return nullptr;
}

void Graph::increment_graph_order()
{
    this->_order += 1;
}

vector<vector<long int>> Graph::get_graph_matrix()
{
    return this->graph_matrix;
}

Solution* Graph::get_best_solution()
{
    return this->best_solution;
}

void Graph::set_node_coordinates(int id, double x, double y)
{
    Node* node = this->node(id);

    node->set_x_coordinate(x);
    node->set_y_coordinate(y);
}