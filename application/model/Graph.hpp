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

#include "Node.hpp"
#include "GraphGenerator.hpp"
#include "parameters.hpp"

/**
 * \brief klasa reprezentująca graf
 */
class Graph
{
public:
	Graph( const unsigned nodes, const GraphGenerator * generator );

	~Graph();

	unsigned getNodes() const;

	const Node & getNodeStart() const;

	const Node & getNodeEnd() const;

	unsigned getParam( unsigned n, unsigned m, Parameters param ) const;

	void setEndNodes( unsigned start, unsigned end );

	void print() const;

	void printNodes() const;

private:
	void resetEndNodes();
	
	unsigned start;

	unsigned end;

	unsigned nodesNumber;

	Matrix matrix;

	std::vector<Node> nodes;
};

#endif // GRAPH_HPP
