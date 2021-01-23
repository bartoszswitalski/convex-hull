/*
*	Name:		time.hpp
*	Purpose:
*
*	Author:     Piotr Frątczak, Bartosz Świtalski
*
*	Warsaw University of Technology
*	Faculty of Electronics and Information Technology
*/
#include "stopwatch.hpp"

auto Stopwatch::timeAlgorithm(const std::vector<Point>& points, ConvexHull (*algorithm)(const std::vector<Point>&)) {
    auto stopwatchStart = std::chrono::high_resolution_clock::now();

    algorithm(points);

    auto stopwatchStop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( stopwatchStop - stopwatchStart ).count();
    return duration;
}

int Stopwatch::timeAverageNRuns(int runs, const std::vector<Point>& points, ConvexHull (*algorithm)(const std::vector<Point>&)) {
    int averageTime = 0;
    for(int i=0; i < runs; ++i){
        averageTime += timeAlgorithm(points, algorithm);
    }
    return averageTime/runs;
}

void Stopwatch::examineAlgorithm(int points, int seed, int problems, int step, int runs, ConvexHull (*algorithm)(const std::vector<Point>&)){
    std::map<int,int> averageTimes;

    int finalN = points + problems*step;
    for(int n=points; n < finalN; n += step){
        std::vector<Point> pointCloud = generator::generatePoints(seed, n);
        int averageTime = timeAverageNRuns(runs, pointCloud, algorithm);
        averageTimes.emplace(n, averageTime);
    }

    int medianN = points + ( problems - problems%2 ) * step / 2;

    int medianTime = averageTimes.at(medianN);
    signed long medianComplexity = algorithms::getTimeComplexity(medianN, algorithm);

    for(int n=points; n < finalN; n += step){
        int timeN = averageTimes.at(n);
        signed long complexity = algorithms::getTimeComplexity(n, algorithm);

        double qOfN = double(timeN * medianComplexity) / double(complexity * medianTime);
        std::pair<int,double> p = std::make_pair(timeN, qOfN);
        scores.emplace(n, p);
        keys.push_back(n);
    }
}

void Stopwatch::save() {
    try{
        std::ofstream times_file (TIMES_FILE, WRITE_FILE);

        for(int n : keys){
            std::pair<int,double> p = scores.at(n);
            times_file << n        << SEPARATOR
                       << p.first  << SEPARATOR
                       << std::setprecision(2)
                       << std::fixed
                       << p.second << '\n';
        }

        times_file.close();
    }
    catch(const std::ofstream::failure& e){
        std::cout << "ERROR: ostream failed.";
    }
}