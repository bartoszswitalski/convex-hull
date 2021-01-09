/*
*	Name:		main.cpp
*	Purpose:
*
*	Author:     Piotr Frątczak, Bartosz Świtalski
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
*/
#include "test.hpp"
#include "preprocessing.hpp"
#include "algorithms.hpp"

int main(int argc, char* argv[]){
    unitTests();

    // TYMCZASOWE DEMO
    int n = 10;
    std::vector<Point> pts = generator::generatePoints(1234,n);
    std::vector<Point> modelPts = preprocessing::preprocess(pts, 1.2);

    ConvexHull ch = algorithms::naive(modelPts);
    ch.save();
}