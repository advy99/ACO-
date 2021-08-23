#ifndef TESTS_GRAPH_HPP
#define TESTS_GRAPH_HPP

#include <gtest/gtest.h>

#include "Graph.hpp"


TEST (Graph, EmptyConstructor) {
	Graph<int> my_graph;

	EXPECT_EQ(0, my_graph.num_nodes());
	
}

TEST (Graph, TwoCitiesNotConnected) {
	Graph<double> my_graph(2);

	EXPECT_FALSE(my_graph.is_connected(0, 1));

}


#endif
