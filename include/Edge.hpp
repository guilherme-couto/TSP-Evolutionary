#ifndef EDGE_HPP
#define EDGE_HPP

#include "defines.hpp"

class Edge
{
    public:
        Edge(int target_id, int target_position);
        ~Edge();

        int target_id();
        int target_position();
        double weight();
        Edge* next_edge();

        void set_next_edge(Edge* edge);
        void set_weight(double weight);

    private:
        Edge* _next_edge;
        int _target_id;
        int _target_position;
        double _weight;
};

#endif /* EDGE_HPP */