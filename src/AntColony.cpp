#include "AntColony.hpp"


AntColony :: AntColony (const Graph<double> & paths, const uint16_t num_ants,
							   const double pheromones_evaporation_rate,
								const double pheromones_importance,
								const double probability_explotation_behaviour,
								const double rho) {
	paths_ = paths;

	pheromones_evaporation_rate_ = pheromones_evaporation_rate;
	rho_ = rho;

	pheromones_ = Graph<double>(paths.num_nodes());

	Ant::set_pheromones_importance(pheromones_importance);
	Ant::set_probability_explotation_behaviour(probability_explotation_behaviour);

	init_ants(num_ants);

}

void AntColony :: clear() {

	if (ants_.size() > 0) {
		init_ants(ants_.size());
	}

	pheromones_ = Graph<double>(paths_.num_nodes());
}

void AntColony :: change_paths_and_clear(const Graph<double> & paths) {
	paths_ = paths;

	clear();
}

void AntColony :: init_ants(const uint16_t num_ants)  {

	ants_.clear();
	ants_.resize(num_ants);

	for (auto & ant: ants_) {
		ant = Ant();
	}

}

Graph<double> AntColony :: paths() const {
	return paths_;
}

Graph<double> AntColony :: pheromones() const {
	return pheromones_;
}

void AntColony :: update_pheromones(const std::vector<uint32_t> & best_path, const double best_path_length) noexcept {
	
	for (uint32_t i = 0; i < best_path.size(); i++) {
		double new_pheromones_value = 0.0;

		uint32_t j = (i + 1) % best_path.size();
			
		new_pheromones_value = (1 - pheromones_evaporation_rate_) * pheromones_.cost(i, j);

		new_pheromones_value += pheromones_evaporation_rate_ * std::pow(best_path_length, -1);
		
		pheromones_.connect(i, j, new_pheromones_value);	
	}
	
}

void AntColony :: local_update_pheromones(const uint32_t position, const uint32_t new_position) noexcept {

	double new_pheromones_value = (1 - rho_) * pheromones_.cost(position, new_position);

	new_pheromones_value += rho_ * initial_pheromones_;
	
	pheromones_.connect(position, new_position, new_pheromones_value);

}


void AntColony :: calculate_initial_pheromones() {
	// we will use a greedy algorithm to calculate this parameter

	// we use a greedy ant that start at the position 0
	Ant greedy_ant(0);
	
	uint32_t best_city = 1;
	double best_city_cost = std::numeric_limits<double>::infinity();

	while(greedy_ant.get_path().size() < paths_.num_nodes()) {
		
		uint32_t ant_position = greedy_ant.position();
		best_city_cost = std::numeric_limits<double>::infinity();
		
		for ( uint32_t i = 0; i < paths_.num_nodes(); i++ ) {
			if (!greedy_ant.visited(i) && i != ant_position && paths_.cost(ant_position, i) < best_city_cost) {
				best_city_cost = paths_.cost(ant_position, i);
				best_city = i;
			}
		}

		greedy_ant.move_to_position(best_city);

	}

	initial_pheromones_ = paths_.num_nodes() * greedy_ant.get_path_length(paths_);

	std::vector<uint32_t> path = greedy_ant.get_path();

	for ( uint32_t i = 0; i < path.size() - 1; i++) {
		pheromones_.connect(i, i+1, initial_pheromones_);
	}

	pheromones_.connect(path.front(), path.back(), initial_pheromones_);

}

std::pair<std::vector<uint32_t>, double> AntColony :: run_simulation (const uint32_t num_iterations) {

	calculate_initial_pheromones();

	uint16_t iteration = 0;
	bool stop_running = num_iterations == iteration;

	double iteration_best_path_length;
	std::vector<uint32_t> iteration_best_path;

	double global_best_path_length = std::numeric_limits<double>::infinity();
	std::vector<uint32_t> global_best_path;

	while (!stop_running) {

		iteration_best_path_length = std::numeric_limits<double>::infinity();
		
		// All ants at the start of the path, and need to complete a route
		for (Ant & ant: ants_) {
			ant.clear_path();
			// Ants will start at a random position
			ant.move_to_position(Random::next_int(paths_.num_nodes()));	

			while ( ant.get_path().size() < paths_.num_nodes() ) {
				uint32_t new_position = ant.select_path(paths_, pheromones_);

				local_update_pheromones(ant.position(), new_position);
				
				ant.move_to_position(new_position);

			}

			double path_length = ant.get_path_length(paths_);

			if (path_length < iteration_best_path_length) {
				iteration_best_path = ant.get_path();
				iteration_best_path_length = path_length;
			}
	
			if (path_length < global_best_path_length) {
				global_best_path_length = path_length;
				global_best_path = ant.get_path();
			}

		}

		update_pheromones(global_best_path, global_best_path_length);

		iteration++;

		stop_running = num_iterations == iteration;
	}
	
	return std::make_pair(global_best_path, global_best_path_length);

}

