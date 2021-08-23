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

TEST (Graph, CityNotConnectedWithItself) {
	Graph<double> my_graph(2);

	EXPECT_FALSE(my_graph.is_connected(0, 0));

}


TEST (Graph, CitiesConnected) {
	Graph<double> my_graph(4);

	my_graph.connect(1, 3, 23.2);

	EXPECT_FALSE(my_graph.is_connected(0, 3));
	EXPECT_TRUE(my_graph.is_connected(1, 3));
	EXPECT_TRUE(are_equals(23.2, my_graph.cost(1, 3)));

}

TEST (Graph, CheckNumNodes) {
	Graph<double> my_graph(4);


	EXPECT_EQ(4, my_graph.num_nodes());

}


TEST (Graph, DisconnectCities) {
	Graph<double> my_graph(4);

	my_graph.connect(1, 3, 23.2);

	EXPECT_FALSE(my_graph.is_connected(0, 3));
	EXPECT_TRUE(my_graph.is_connected(1, 3));
	EXPECT_TRUE(are_equals(23.2, my_graph.cost(1, 3)));

	my_graph.disconnect(3, 1);

	EXPECT_FALSE(my_graph.is_connected(1, 3));
	EXPECT_TRUE(are_equals(0.0, my_graph.cost(1, 3)));
}


#endif
