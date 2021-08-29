#include "Ant.hpp"

Ant :: Ant(const uint32_t start_position) : path_(1, start_position), path_legth_(0)
{}


void Ant :: move_to_position (const uint32_t new_position) noexcept {
	path_.push_back(new_position);
}

uint32_t Ant :: position() const noexcept {
	return path_.back();
}


uint32_t Ant :: select_best_path (const Graph<double> & paths, 
										    const Graph<double> & pheromones) const noexcept {

	double best_city_importance = std::numeric_limits<double>::infinity();
	uint32_t best_city = 0;

	// from all non-visited cities, visit the best one
	for (uint32_t num_city = 0; num_city < paths.num_nodes(); num_city++) {
		if (!visited(num_city, position() )) {
			double inverse_of_distance = 1.0 / paths.cost(position(), num_city);
			double importance = pheromones.cost(num_city, position()) * std::pow(inverse_of_distance, pheromones_importance_); 

			if (importance < best_city_importance) {
				best_city = num_city;
				best_city_importance = importance;
			} 
		}
	}

	return best_city;

}


uint32_t Ant :: select_path_exploring(const Graph<double> & paths, 
												  const Graph<double> & pheromones) const noexcept {

	double total_non_visited_importance = 0.0; 

	// we must get the sum of importance of non-visited nodes first to use this
	// value next
	for (uint32_t num_city = 0; num_city < paths.num_nodes(); num_city++) {
		if (!visited(num_city, position())) {
			double inverse_of_distance = 1.0 / paths.cost(position(), num_city);
			total_non_visited_importance += pheromones.cost(num_city, position()) * std::pow(inverse_of_distance, pheromones_importance_); 
		}

	}
	

	// get a probability for each city
	for (uint32_t num_city = 0; num_city < paths.num_nodes(); num_city++) {

		double probability_select_this = 0.0;

		if (paths.is_connected(num_city, position()) && !visited(num_city) ) {
			double inverse_of_distance = 1.0 / paths.cost(position(), num_city);

			probability_select_this = pheromones.cost(position(), num_city) * std::pow(inverse_of_distance, pheromones_importance_); 
	
			probability_select_this /= total_non_visited_importance;

		} 

		// TODO: Store probabilities and select one random city based on these prob.

	}

	return TODO;

	
}

uint32_t Ant :: select_path (const Graph<double> & paths, 
									  const Graph<double> & pheromones) const noexcept {
	

	uint32_t next_node;

	bool explotation = Random::next_float() < explotation_behaviour_;

	if (explotation) {
		next_node = select_best_path(paths, pheromones); 

	} else {
		next_node = select_path_exploring(paths, pheromones); 
	}

}
