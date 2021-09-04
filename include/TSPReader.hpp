#ifndef TSPREADER_HPP
#define TSPREADER_HPP

#include "Graph.hpp"

#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

enum class EdgeWeightTypes {EUCLIDEAN_2D, UNKNOWN};

struct Point {
	double x;
	double y;
};

class TSPReader {
	private:
		static double calculate_distance(const Point & p1, const Point & p2, const EdgeWeightTypes & distance_type);

	public:
		
		static std::pair<Graph<double>, std::vector<Point> > read_from_file(const std::string & file);
		static Graph<double> read_matrix_from_file(const std::string & file);

};

#endif
