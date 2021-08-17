#ifndef ANTCOLONY_HPP
#define ANTCOLONY_HPP 


#include "Graph.hpp"

class AntColony {
	private:

		static const double pheromones_evaporation_rate_;

		Graph<double> paths_;
		Graph<double> pheromones_;

		std::vector<Ant> ants_;

		void update_pheromones();

		void init_ants(const uint16_t num_ants, const double ants_visibility, 
							const double pheromones_per_ant) noexcept;

	public:

		AntColony(const Graph<double> & paths, const uint16_t num_ants, 
					 const double ants_visibility, const double pheromones_per_ant);

		AntColony(const AntColony & other) = default;

		void run_simulation() noexcept;

		void clear(const std::optional<Graph<double> > & maybe_path = {}) noexcept;



};



#endif
