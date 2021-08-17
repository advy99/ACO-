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

	public:

		AntColony(const Graph<double> & paths, const uint16_t num_ants);


};



#endif
