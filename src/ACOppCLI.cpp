#include "AntColony.hpp"

#include <iostream>

int main (int argc, char ** argv) {
	
	if ( argc < 3) {
		std::cerr << "ERROR: Incorrect number of parameters.\n"
					 << "\t Use: " << argv[0] << " <num_ants> <num_iterations>\n";

		std::exit(-1);
	}

	int num_ants = std::atoi(argv[1]);
	int iterations = std::atoi(argv[2]);

	int num_cities = 6;

	Graph<double> paths(num_cities);

	for ( int32_t i = 0; i < num_cities; i++) {
		for (int32_t j = i + 1; j < num_cities; j++) {
			paths.connect(i, j, Random::next_float(10.0, 500.0));
		}
	}

	std::cout << "Paths: \n\n";
	for ( int32_t i = 0; i < num_cities; i++) {
		for (int32_t j = i; j < num_cities; j++) {
			std::cout << paths.cost(i, j) << " ";
		}
		std::cout << "\n";
	}

	AntColony my_colony(paths, num_ants);

	auto solution = my_colony.run_simulation(iterations);

	std::cout << "Path length: " << solution.second << "\nPath:\n";

	for (auto & element : solution.first) {
		std::cout << element << " ";
	}

	std::cout << "\n";

}
