#include "AntColony.hpp"


AntColony :: AntColony (const Graph<double> & paths, const uint16_t num_ants,
								const double ants_visibility, const double pheromones_per_ant,
							   const double pheromones_evaporation_rate) {
	paths_ = paths;

	pheromones_evaporation_rate_ = pheromones_evaporation_rate;

	pheromones_ = Graph<doubles>(paths.num_nodes());

	Ant::set_visibility(ants_visibility);
	Ant::set_pheromones_deposited(pheromones_per_ant);

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

void AntColony :: run_simulation () noexcept {

	bool all_ants_have_path = false;
	bool stop_running = false;

	// TODO: Define a stop condition
	while (!stop_running) {
		
		all_ants_have_path = false;
		
		// All ants at the start of the path
		for (Ant & ant: ants_) {
			ant.update_position(0);	
		}
		
		while (!all_ants_have_path) {

		}

		update_pheromones();


	}
	

}


