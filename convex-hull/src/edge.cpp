/*
*	Name:		edge.cpp
*	Purpose:
*
*	@author
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
*/
#include "../lib/edge.hpp"

Edge::Edge(Point points[EDGE_POINTS]){
    for(int i = 0; i < EDGE_POINTS; ++i){
        this->points[i] = points[i];
    }
}