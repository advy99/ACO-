#ifndef TESTS_GRAPH_HPP
#define TESTS_GRAPH_HPP

#include <gtest/gtest.h>

#include "Graph.hpp"


TEST (Graph, EmptyConstructor) {
	Graph<int> my_graph;

	EXPECT_EQ(0, my_graph.num_nodes());
	
}


#endif
