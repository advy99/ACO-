#ifndef ANT_HPP
#define ANT_HPP


class Ant {
	private:
		uint32_t position_;

		const double node_visibility_;
		const double pheromones_deposited_;
		

	public:

		uint32_t select_path(const Graph<double> & paths, const Graph<double> & pheromones) const noexcept;

		double calculate_pheromones(const uint32_t destination, const Graph<double> & pheromones) const noexcept;

		void update_position(const uint32_t new_position) noexcept;
		
		uint32_t position() const noexcept;

};


#endif
