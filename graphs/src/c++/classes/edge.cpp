#include "edge.hpp"

Edge::Edge(Node source_node, Node destination_node, int weight, EdgeTypes type)
    : source_node(source_node), destination_node(destination_node), weight(weight), type(type) {}