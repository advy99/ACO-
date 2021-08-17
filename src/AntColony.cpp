#include "AntColony.hpp"


AntColony :: AntColony (const Graph<double> & paths, const uint16_t num_ants,
								const double ants_visibility, const double pheromones_per_ant) {
	paths_ = paths;

	pheromones_ = Graph<doubles>(paths.num_nodes());

	Ant::set_visibility(ants_visibility);
	Ant::set_pheromones_deposited(pheromones_per_ant);

	init_ants(num_ants);

}

void AntColony :: clear(const std::optional<Graph<double> > & maybe_path) noexcept {

	if (maybe_path) {
		paths_ = maybe_path.value();
	}

	if (ants_.size() > 0) {
		init_ants(ants_.size());
	}

	pheromones_ = Graph<doubles>(paths.num_nodes());
}

void AntColony :: init_ants(const uint16_t num_ants) noexcept {

	ants_.clear();
	ants_.resize(num_ants);

	for (auto & ant: ants_) {
		ant = Ant();
	}

}
