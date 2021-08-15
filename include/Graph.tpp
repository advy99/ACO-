#ifndef GRAPH_TPP
#define GRAPH_TPP 

template <typename T>
Graph<T> :: Graph (const uint16_t num_nodes) :num_nodes_(num_nodes) {
	
	paths_weights_.resize(num_nodes);

	// NOTE: In this implementation of Graph the direction does not matter in costs
	for (uint16_t i = 0; i < num_nodes; i++) {
		paths_weights_[i] = std::vector<T>(num_nodes - i, 0);
	}
}

template <typename T>
uint16_t Graph<T> :: num_nodes() const noexcept {
	return num_nodes_;
}


template <typename T>
bool Graph<T> :: is_connected ( const uint16_t first_node, const uint16_t second_node) {

	T cost_between_nodes = cost(first_node, second_node);

	bool result;

	if constexpr (std::is_floating_point_v<T>) {
		// NOTE: Leave "- 0.0" for readability, i want cost_between_nodes to be zero
		result = std::fabs(cost_between_nodes - 0.0) < std::numeric_limits<T>::epsilon();
	} else {
		result = cost_between_nodes != 0;
	}

	result = result || first_node == second_node;

	return cost(first_node, second_node) != 0 || first_node == second_node; 
}

template <typename T>
void Graph<T> :: disconnect (const uint16_t first_node, const uint16_t second_node) noexcept {
	connect(first_node, second_node, 0);
}

template <typename T>
void Graph<T> :: connect (uint16_t first_node,  uint16_t second_node, const T cost) noexcept {

	if ( first_node < second_node ) {
		std::swap(first_node, second_node);
	}
	
	paths_weights_[first_node][second_node] = cost;

}

template <typename T>
T Graph<T> :: cost(const uint16_t first_node, const uint16_t second_node) const noexcept {
	if ( first_node < second_node ) {
		std::swap(first_node, second_node);
	}

	return paths_weights_[first_node][second_node];
}


#endif

