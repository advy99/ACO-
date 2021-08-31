#ifndef ANTCOLONY_HPP
#define ANTCOLONY_HPP 


#include "Graph.hpp"

class AntColony {
	private:

		double pheromones_evaporation_rate_;

		Graph<double> paths_;
		Graph<double> pheromones_;

		std::vector<Ant> ants_;

		void update_pheromones(const std::vector<uint32_t> & best_path);

		void init_ants(const uint16_t num_ants) noexcept;

	public:

		AntColony(const Graph<double> & paths, const uint16_t num_ants, 
					 const double pheromones_evaporation_rate = 0.1,
					 const double pheromones_importance = 2,
					 const double probability_explotation_behaviour = 0.9);

		AntColony(const AntColony & other) = default;

		~AntColony() = default;

		void run_simulation() noexcept;

		void clear() noexcept;

		void change_paths_and_clear(const Graph<double> & paths) noexcept;

		Graph<double> paths() const noexcept;

		Graph<double> pheromones() const noexcept;

		AntColony & operator = (const AntColony & other) = default;


};



#endif
