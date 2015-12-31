/** 
 *  \file   Graph.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Graph.
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <array>

#include "GraphGenerator.hpp"

/**
 * \brief klasa reprezentująca graf
 */
class Graph
{
public:
	Graph( const std::string & file );

	Graph( const unsigned nodes, const GraphGenerator * generator );

	~Graph();

	void rate( const std::array<unsigned short, (unsigned)Parameters::Count> & weights );

	unsigned getRating( unsigned first, unsigned second );

	void print();

	void printRates();

private:
	unsigned nodes;

	AdjacencyMatrix adjacencyMatrix;
	
	RatingMatrix ratingMatrix;
};

#endif // GRAPH_HPP
