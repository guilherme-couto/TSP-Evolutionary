#include "Node.hpp"


Node::Node(int id)
{
    this->_first_edge = nullptr;
    this->_last_edge = nullptr;
    this->_next_node = nullptr;

    this->_id = id;
    this->_position = 0;
    this->_in_degree = 0;
    this->_out_degree = 0;
    this->_degree = 0;      // Only for undirected graphs
    this->_visited = false;
}

Node::~Node()
{
    // delete automático agora
}

Edge* Node::first_edge()
{
    return this->_first_edge;
}

Edge* Node::last_edge()
{
    return this->_last_edge;
}

Node* Node::next_node()
{
    return this->_next_node;
}

Edge* Node::edge_for(int target_id)
{
    if(this->_first_edge != nullptr)
    {
        for(Edge* aux_edge = this->first_edge(); aux_edge != nullptr; aux_edge = aux_edge->next_edge())
        {
            if(aux_edge->target_id() == target_id)
            {
                return aux_edge;
            }
        }
    }
    return nullptr;
}

int Node::id()
{
    return this->_id;
}

int Node::in_degree()
{
    return this->_in_degree;
}

int Node::out_degree()
{
    return this->_out_degree;
}

int Node::degree()
{
    return this->_degree;
}

int Node::remove_edge(int id, bool directed, Node* target_node)
{
    // TODO: implement
    return -1;
}

int Node::position()
{
    return this->_position;
}

bool Node::has_edge_for(int target_id)
{
    if(this->_first_edge != nullptr)
    {
        for(Edge* aux_edge = this->first_edge(); aux_edge != nullptr; aux_edge = aux_edge->next_edge())
        {
            if(aux_edge->target_id() == target_id)
            {
                return true;
            }
        }
    }
    return false;
}

void Node::set_next_node(Node* node)
{
    this->_next_node = node;
}

void Node::insert_edge(int target_id, int target_position, double weight)
{
    Edge* edge(new Edge(target_id, target_position));
    edge->set_weight(weight);
    if(this->first_edge() != nullptr)
    {
        this->_last_edge->set_next_edge(edge);
        this->_last_edge = edge;
    }
    else
    {
        this->_first_edge = edge;
        this->_last_edge = this->_first_edge;
    }

    this->_degree++;
}

void Node::increment_out_degree()
{
    this->_out_degree += 1;
}

void Node::increment_in_degree()
{
    this->_in_degree += 1;
}

void Node::decrement_out_degree()
{
    this->_out_degree -= 1;
}

void Node::decrement_in_degree()
{
    this->_in_degree -= 1;
}

void Node::increment_degree()
{
    this->_degree += 1;
}

void Node::decrement_degree()
{
    this->_degree -= 1;
}

void Node::set_position(int position)
{
    this->_position = position;
}

void Node::set_visited(bool visited)
{
    this->_visited = visited;
}

void Node::set_x_coordinate(double x_coordinate)
{
    this->_x_coordinate = x_coordinate;
}

void Node::set_y_coordinate(double y_coordinate)
{
    this->_y_coordinate = y_coordinate;
}

double Node::x_coordinate()
{
    return this->_x_coordinate;
}

double Node::y_coordinate()
{
    return this->_y_coordinate;
}