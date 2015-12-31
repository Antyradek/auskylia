/** 
 *  \file   Graph.cpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Definicja klasy Graph.
 */

#include "Graph.hpp"

#include "debug.hpp"

Graph::Graph( const std::string & file )
{
}

Graph::Graph( const unsigned nodes, const GraphGenerator * generator ) : nodes(nodes)
{
	DBG("Graph( " << nodes << " )");

	generator->generate( nodes, adjacencyMatrix );

	for (auto i : ratingMatrix)
		for (unsigned rating : i)
			rating = 0;
}

Graph::~Graph()
{
}

void Graph::rate( const std::array<unsigned short, (unsigned)Parameters::Count> & weights )
{
	for ( unsigned i = 0; i < nodes; ++i)
	{
		for ( unsigned j = 0; j < i; ++j )
		{
		 	for ( unsigned k = 0; k < (unsigned)Parameters::Count; ++k ) 
			{
				ratingMatrix[ i ][ j ] += adjacencyMatrix[ i ][ j ][ k ] * weights[ k ];
				ratingMatrix[ j ][ i ] = ratingMatrix[ i ][ j ];
			}	
		}
	}

}

unsigned Graph::getRating( unsigned first, unsigned second )
{
	return ratingMatrix[ first ][ second ];
}

#include <iostream>

void Graph::print()
{
	for ( unsigned i = 0; i < nodes; ++i)
	{
		std::cout << i << ": ";

		for ( unsigned j = i+1; j < nodes; ++j )
		{
			std::cout << j << "[ ";

		 	for ( unsigned k = 0; k < (unsigned)Parameters::Count; ++k ) 
			{
				std::cout << adjacencyMatrix[ i ][ j ][ k ] << " ";
			}	
			std::cout << "]  ";
		}

		std::cout << std::endl;
	}
}
