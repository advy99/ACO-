#include "AntColony.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

Graph<double> read_from_file(std::string file) {

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



	Graph<double> paths = read_from_file(file);

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
