#include "TSPReader"

#include <cmath>

double TSPReader :: calculate_distance (const Point & p1, const Point & p2, const EdgeWeightTypes edge_type) {

	double result = 0.0;

	if (edge_type == EdgeWeightTypes::EUCLIDEAN_2D) {
		double x_difference = p2.x - p1.x;
		double y_difference = p2.y - p1.y;
		result = std::sqrt( std::pow(x_difference, 2) + std::pow(y_difference, 2) );
	} else {
		throw std::runtime_error("Unkown type of edge weight");
	}


	return result;

}


