#ifndef NODE_HPP
#define NODE_HPP

#include "defines.hpp"
#include "Edge.hpp"

class Node
{
    public:
        Node(int id);
        ~Node();

        Edge* first_edge();
        Edge* last_edge();
        Node* next_node();
        Edge* edge_for(int target_id);

        int id();
        int in_degree();
        int out_degree();
        int degree();   // Only for undirected graphs
        bool visited();
        int remove_edge(int id, bool directed, Node* target_node);
        int position();
        bool has_edge_for(int target_id);
        double x_coordinate();
        double y_coordinate();

        void set_next_node(Node* node);
        void insert_edge(int target_id, int target_position, double weight);
        void increment_out_degree();
        void increment_in_degree();
        void decrement_out_degree();
        void decrement_in_degree();
        void increment_degree();    // Only for undirected graphs
        void decrement_degree();    // Only for undirected graphs
        void set_position(int position);
        void set_visited(bool visited);
        void set_x_coordinate(double x_coordinate);
        void set_y_coordinate(double y_coordinate);

    private:
        Edge* _first_edge;
        Edge* _last_edge;
        Node* _next_node;

        unsigned int _id;
        unsigned int _position;
        unsigned int _in_degree;
        unsigned int _out_degree;
        unsigned int _degree;   // Only for undirected graphs
        bool _visited;
        double _x_coordinate;
        double _y_coordinate;
};

#endif /* NODE_HPP */