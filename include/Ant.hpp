#ifndef ANT_HPP
#define ANT_HPP

#include "aux.hpp"
#include "Graph.hpp"

class Ant {
	private:

		std::vector<uint32_t> path_; 

		// all ants will see the same nodes and deposit the same number of pheromones
		static double pheromones_importance_;
		static double probability_explotation_behaviour_;
		
		
		uint32_t select_best_path(const Graph<double> & paths, const Graph<double> & pheromones) const noexcept;

		uint32_t select_path_exploring(const Graph<double> & paths, const Graph<double> & pheromones) const;

	public:

		explicit Ant(const uint32_t start_position = 0);

		Ant(const Ant & other) = default;

		~Ant() = default;

		uint32_t select_path(const Graph<double> & paths, const Graph<double> & pheromones) const;

		double calculate_pheromones(const uint32_t destination, const Graph<double> & pheromones) const noexcept;

		void move_to_position(const uint32_t new_position);
		
		uint32_t position() const noexcept;

		bool visited(const uint32_t node) const noexcept;

		std::vector<uint32_t> get_path() const;

		void clear_path() noexcept;


		static double pheromones_importance()  ;

		static void set_pheromones_importance(const double new_pheromones_importance) ;

		static double probability_explotation_behaviour()  ;

		static void set_probability_explotation_behaviour(const double new_probability) ;


		double get_path_length(const Graph<double> & paths) const noexcept;

		Ant & operator = (const Ant & other) = default; 

};


#endif
