#include "TSPReader.hpp"


double TSPReader :: calculate_distance (const Point & p1, const Point & p2, const EdgeWeightTypes & edge_type) {

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


std::pair<Graph<double>, std::vector<Point> > TSPReader :: read_from_file(const std::string & file) {
	std::ifstream file_reader(file);

	if (!file_reader) {
		throw std::runtime_error("Could not open " + file);
	}

	Graph<double> paths;
	std::vector<Point> points;
	int32_t dimension;

	std::string word;
	bool file_is_tsp_valid = false;

	EdgeWeightTypes edge_type = EdgeWeightTypes::UNKNOWN;

	file_reader >> word;

	while(!file_reader.eof() && word != "TYPE") {
		file_reader >> word;
	}

	file_is_tsp_valid = word == "TYPE";

	if (file_is_tsp_valid) {
		// read the " : " 
		file_reader >> word;

		// read if the type is TSP
		file_reader >> word;
		file_is_tsp_valid = word == "TSP" && !file_reader.eof();
	}

	if (file_is_tsp_valid) {
		// read dimensions
		file_reader >> word;

		while(!file_reader.eof() && word != "DIMENSION") {
			file_reader >> word;
		}

		file_reader >> word;
		file_reader >> word;

		dimension = std::atoi(word.c_str());

		points.resize(dimension);


		// read edge types
		file_reader >> word;

		while(!file_reader.eof() && word != "EDGE_WEIGHT_TYPE") {
			file_reader >> word;
		}

		file_reader >> word;
		file_reader >> word;
		
		if (word == "EUC_2D") {
			edge_type = EdgeWeightTypes::EUCLIDEAN_2D; 
		}

		// read until start of cities
		file_reader >> word;

		while(!file_reader.eof() && word != "NODE_COORD_SECTION") {
			file_reader >> word;
		}

		for (int32_t i = 0; i < dimension; i++) {
			// first word is the num of the city
			file_reader >> word;
			file_reader >> points[i].x;
			file_reader >> points[i].y;
		}

		paths = Graph<double>(points.size());

		for (uint32_t i = 0; i < points.size(); i++) {
			for(uint32_t j = i + 1; j < points.size(); j++) {
				paths.connect(i, j, calculate_distance(points[i], points[j], edge_type));
			}
		}
		

	}


	return std::make_pair(paths, points);

}


Graph<double> TSPReader :: read_matrix_from_file(const std::string & file) {

	std::ifstream f(file);

	if ( !f ) {
		throw std::runtime_error("Error opening " + file);
	}

	std::string line;

	std::getline(f, line);

	uint32_t num_line = 0;
	uint32_t num_cities = 0;
	
	double value;
	std::vector<double> first_line;
	std::istringstream iss_f(line);

	while (!iss_f.eof()) {
		iss_f >> value;
		first_line.push_back(value);
	}

	num_cities = first_line.size();

	Graph<double> solution(num_cities, 0);

	for (unsigned int i = 0; i < first_line.size(); i++) {
		solution.connect(0, i, first_line[i]);
	}

	std::getline(f, line);
	num_line++;
	
	uint32_t num_val = 0;

	while(!f.eof()) {	
		std::istringstream iss(line);
		num_val = 0;
		while (!iss.eof()) {
			iss >> value;
			if (num_val > num_line) {
				solution.connect(num_line, num_val, value);
			}
			num_val++;
		}

			
		std::getline(f, line);
		num_line++;
	}

	return solution;
}
