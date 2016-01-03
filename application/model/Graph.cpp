/** 
 *  \file   Graph.cpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Definicja klasy Graph.
 */

#include <iostream>

#include "Graph.hpp"

#include "debug.hpp"

Graph::Graph( const std::string & file )
{
}

Graph::Graph( const unsigned nodesNumber, const GraphGenerator * generator ) : nodesNumber(nodesNumber)
{
	matrix = Matrix (nodesNumber, std::vector< std::array< unsigned, (unsigned)Parameters::Count > > (nodesNumber) );

	DBG("Graph( " << nodesNumber << " )");
	
	nodes = std::vector<Node> (nodesNumber);

	generator->generate( nodes, matrix );
}

Graph::~Graph()
{
}

unsigned Graph::getNodes() const
{
	return nodes.size();
}

unsigned Graph::getParam( unsigned n, unsigned m, Parameters param ) const
{
	return matrix[ n ][ m ][ (unsigned)param ];
}

void Graph::print() const
{
	DBG("Graph::print");

	for ( unsigned i = 0; i < nodesNumber; ++i)
	{
		std::cout << i << ": ";

		for ( unsigned j = i+1; j < nodesNumber; ++j )
		{
			std::cout << j << "[ ";

		 	for ( unsigned k = 0; k < (unsigned)Parameters::Count; ++k ) 
			{
				std::cout << matrix[ i ][ j ][ k ] << " ";
			}	
			std::cout << "]  ";
		}

		std::cout << std::endl;
	}
}

void Graph::printNodes() const
{
	DBG("Graph::printNodes()");

	for( unsigned i = 0; i<nodesNumber; ++i )
	{
		std::cout << "[" << i << "]: ";
		nodes[i].print();
		std::cout << std::endl;
	}
}
