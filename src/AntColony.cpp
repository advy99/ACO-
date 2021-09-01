#include "AntColony.hpp"


AntColony :: AntColony (const Graph<double> & paths, const uint16_t num_ants,
							   const double pheromones_evaporation_rate,
								const double pheromones_importance,
								const double probability_explotation_behaviour) {
	paths_ = paths;

	pheromones_evaporation_rate_ = pheromones_evaporation_rate;

	pheromones_ = Graph<doubles>(paths.num_nodes());

	Ant::set_pheromones_importance(pheromones_importance);
	Ant::set_probability_explotation_behaviour(probability_explotation_behaviour);

	init_ants(num_ants);

}

void AntColony :: clear() noexcept {

	if (ants_.size() > 0) {
		init_ants(ants_.size());
	}

	pheromones_ = Graph<doubles>(paths.num_nodes());
}

void AntColony :: change_paths_and_clear(const Graph<double> & paths) noexcept {
	paths_ = paths;

	clear();
}

void AntColony :: init_ants(const uint16_t num_ants) noexcept {

	ants_.clear();
	ants_.resize(num_ants);

	for (auto & ant: ants_) {
		ant = Ant();
	}

}

Graph<double> AntColony :: paths() const noexcept {
	return paths_;
}

Graph<double> AntColony :: pheromones() const noexcept {
	return pheromones_;
}

void AntColony :: update_pheromones(const std::vector<uint32_t> & best_path) {
	
	// TODO: Dont iterate all graph, only connections of best_path

	for (uint16_t i = 0; i < pheromones_.num_nodes(); i++) { 
		for (uint16_t j = i; j < pheromones_.num_nodes(); j++) { 
			double new_pheromones_value = 0.0;
			
			new_pheromones_value = (1 - pheromones_evaporation_rate_) * pheromones_.cost(i, j);

			// search if two cities are next to each other in the path
			auto i_in_best_path = std::find(best_path.begin(), best_path.end(), i);
			auto j_in_best_path = std::find(best_path.begin(), best_path.end(), j);
			auto distance_between_i_and_j = std::abs(std::distance(i_in_best_path, j_in_best_path));

			if ( distance_between_i_and_j == 1 || distance_between_i_and_j == pheromones_.num_nodes() ) {
				new_pheromones_value += pheromones_evaporation_rate_ * std::pow(std::accumulate(best_path.begin(), best_path.end()), -1);
			}

			pheromones_.connect(i, j, new_pheromones_value);
		}
	}
	
}

void AntColony :: run_simulation (const uint32_t num_iterations) noexcept {

	uint16_t iteration = 0;
	bool stop_running = num_iterations == iteration;

	double best_path_length;

	// TODO: Define a stop condition
	while (!stop_running) {
		
		all_ants_have_path = false;

		best_path_length = std::numeric_limits<double>::infinity();
		
		// All ants at the start of the path, and need to complete a route
		for (Ant & ant: ants_) {
			ant.clear_path();
			// Ants will start at a random position
			ant.update_position(Random::next_int(paths_.num_nodes()));	

			while ( ant.get_path().size() < paths_.num_nodes() ) {
				uint32_t new_position = ant.select_path(paths_, pheromones_);

				local_update_pheromones(ant.position(), new_position);
				
				ant.move_to_position(new_position);

			}


			if (ant.get_path_length() < best_path_length) {
				best_path_ = ant.get_path();
				best_path_length = ant.get_path_length();
			}
		}

		update_pheromones(best_path_);

		iteration++;

		stop_running = num_iterations == iteration;
	}
	

}


std::vector<double> AntColony :: best_path() const noexcept {
	return best_path_;
}

