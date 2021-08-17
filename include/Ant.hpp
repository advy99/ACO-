#ifndef ANT_HPP
#define ANT_HPP

#include "aux.hpp"
#include "Graph.hpp"

class Ant {
	private:
		uint32_t position_;

		// all ants will see the same nodes and deposit the same number of pheromones
		static double node_visibility_;
		static double pheromones_deposited_;
		

	public:

		explicit Ant(const uint32_t position = 0);

		Ant(const Ant & other) = default;

		~Ant() = default;

		uint32_t select_path(const Graph<double> & paths, const Graph<double> & pheromones) const noexcept;

		double calculate_pheromones(const uint32_t destination, const Graph<double> & pheromones) const noexcept;

		void update_position(const uint32_t new_position) noexcept;
		
		uint32_t position() const noexcept;


		static double visibility() const noexcept;

		static double pheromones_deposited() const noexcept;

		static void set_visibility(const double visibility) noexcept;

		static void set_pheromones_deposited(const double pheromones_per_ant) noexcept;

		Ant & operator = (const Ant & other) = default; 

};


#endif
