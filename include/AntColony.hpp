#ifndef ANTCOLONY_HPP
#define ANTCOLONY_HPP 


#include "Graph.hpp"
#include "Ant.hpp"

class AntColony {
	private:

		double pheromones_evaporation_rate_;
		double rho_;
		double initial_pheromones_;

		Graph<double> paths_;
		Graph<double> pheromones_;

		std::vector<Ant> ants_;

		void update_pheromones(const std::vector<uint32_t> & best_path, const double best_path_length) noexcept;

		void local_update_pheromones(const uint32_t position, const uint32_t new_position) noexcept;

		void init_ants(const uint16_t num_ants);
		
		void calculate_initial_pheromones();

	public:

		AntColony(const Graph<double> & paths, const uint16_t num_ants, 
					 const double pheromones_evaporation_rate = 0.1,
					 const double pheromones_importance = 2,
					 const double probability_explotation_behaviour = 0.9,
					 const double rho = 0.9);

		AntColony(const AntColony & other) = default;

		~AntColony() = default;

		std::pair<std::vector<uint32_t>, double> run_simulation (const uint32_t num_iterations);
		
		void clear() ;

		void change_paths_and_clear(const Graph<double> & paths);

		Graph<double> paths() const;

		Graph<double> pheromones() const;

		AntColony & operator = (const AntColony & other) = default;


};



#endif
