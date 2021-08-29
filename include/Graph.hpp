#ifndef GRAPH_HPP
#define GRAPH_HPP 

#include <vector>
#include <algorithm>
#include <cstdint>


template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
class Graph {
	private:
		uint32_t num_nodes_ = 0;
		std::vector< std::vector<T> > paths_weights_; 

	public:
		
		// Constructors
		
		Graph() = default;

		explicit Graph(const uint32_t num_nodes, const T value = 0);


		// consult methods
		uint32_t num_nodes() const noexcept;

		bool is_connected(const uint32_t first_node, const uint32_t second_node) const noexcept;

		T cost(uint32_t first_node, uint32_t second_node) const noexcept;
		

		// paths modification methods
		void connect(uint32_t first_node, uint32_t second_node, const T cost) noexcept;

		void disconnect(const uint32_t first_node, const uint32_t second_node) noexcept;




};

#include "include/Graph.tpp"

#endif
