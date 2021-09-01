#include "Ant.hpp"

Ant :: Ant(const uint32_t start_position) : path_(1, start_position)
{}


void Ant :: move_to_position (const uint32_t new_position) {
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
												  const Graph<double> & pheromones) const {

	double total_non_visited_importance = 0.0; 

	// we must get the sum of importance of non-visited nodes first to use this
	// value next
	for (uint32_t num_city = 0; num_city < paths.num_nodes(); num_city++) {
		if (!visited(num_city, position())) {
			double inverse_of_distance = 1.0 / paths.cost(position(), num_city);
			total_non_visited_importance += pheromones.cost(num_city, position()) * std::pow(inverse_of_distance, pheromones_importance_); 
		}

	}
	
	std::vector<std::pair<double, uint32_t> > probability_choose_city;

	// get a probability for each city
	for (uint32_t num_city = 0; num_city < paths.num_nodes(); num_city++) {

		if (paths.is_connected(num_city, position()) && !visited(num_city) ) {
			double inverse_of_distance = 1.0 / paths.cost(position(), num_city);

			double probability_select_this = pheromones.cost(position(), num_city) * std::pow(inverse_of_distance, pheromones_importance_); 
	
			probability_select_this /= total_non_visited_importance;

			table_of_probabilities.push_back(std::make_pair(probability_select_this, num_city));

		} 

	}

	double uniform_random = Random::next_float();

	std::size_t i = 0;
	while (i < table_of_probabilities.size() && uniform_random < table_of_probabilities.at(i).first) {
		i++;
	}

	return table_of_probabilities.at(i).second;

}

uint32_t Ant :: select_path (const Graph<double> & paths, 
									  const Graph<double> & pheromones) const  {
	

	uint32_t next_node;

	bool explotation = Random::next_float() < probability_explotation_behaviour_;

	if (explotation) {
		next_node = select_best_path(paths, pheromones); 

	} else {
		next_node = select_path_exploring(paths, pheromones); 
	}

}


bool Ant :: visited(const uint32_t node) const noexcept {
	return std::find(path_.begin(), path_.end(), node) != path.end();
}

void Ant :: clear_path() noexcept {
	path_.clear();
}

std::vector<uint32_t> Ant :: get_path() const  {
	return path_;
}

double Ant :: get_path_length() const noexcept {
	double length = path_.cost(path_.size() - 1, 0);
	
	for (uint32_t i = 0; i < path_.size() - 1; i++) {
		length += path_.cost(i, i+1);
	}

	return length;
}


double Ant :: pheromones_importance() const noexcept {
	return pheromones_importance_;
}


void Ant :: set_pheromones_importance(const double new_pheromones_importance) noexcept {
	pheromones_importance_ = new_pheromones_importance;
}

double Ant :: probability_explotation_behaviour() const noexcept {
	return probability_explotation_behaviour_;
}


void Ant :: set_probability_explotation_behaviour(const double new_probability) noexcept {
	probability_explotation_behaviour_ = new_probability;
}


// default values from ACS paper
double Ant :: pheromones_importance_ = 2;
double Ant :: probability_explotation_behaviour_ = 0.9;

