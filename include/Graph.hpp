#ifndef GRAPH_HPP
#define GRAPH_HPP 

#include <vector>
#include <cstdint>


template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
class Graph {
	private:
		std::vector< std::vector<T> > paths_weights_; 
		uint16_t num_nodes_ = 0;

	public:
		
		// Constructors
		
		Graph() = default;

		Graph(const uint16_t num_nodes);


		// consult methods
		uint16_t num_nodes() const noexcept;

		bool is_connected(const uint16_t first_node, const uint16_t second_node) const noexcept;
		

		// paths modification methods
		void connect(const uint16_t first_node, const uint16_t second_node, const T cost) noexcept;

		void disconnect(const uint16_t first_node, const uint16_t second_node) noexcept;

};

#include "src/Graph.tpp"

#endif
