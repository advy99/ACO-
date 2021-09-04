#include "AntColony.hpp"
#include "TSPReader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>


int main (int argc, char ** argv) {
	
	if ( argc < 4) {
		std::cerr << "ERROR: Incorrect number of parameters.\n"
					 << "\t Use: " << argv[0] << " <num_ants> <num_iterations> <file>\n";

		std::exit(-1);
	}
	
	Random::set_seed(std::time(nullptr));

	int num_ants = std::atoi(argv[1]);
	int iterations = std::atoi(argv[2]);
	std::string file = std::string(argv[3]);



	auto paths = TSPReader::read_from_file(file);

	std::cout << "Paths read from " << file << "\n";
	
	std::cout << std::endl;

	std::cout << "Creating colony and simulating: \n";
	AntColony my_colony(paths, num_ants);

	auto solution = my_colony.run_simulation(iterations);

	std::cout << "Path length: " << solution.second << "\nPath:\n";

	for (auto & element : solution.first) {
		std::cout << element << " ";
	}

	std::vector<uint32_t> uniques;
	std::unique_copy(solution.first.begin(), solution.first.end(), std::back_inserter(uniques));

	std::cout << "\n";
	if ( uniques.size() != solution.first.size()) {
		std::cerr << "ERROR: Somo cities are repeated\n";
	}


}
