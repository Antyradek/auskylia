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

Graph::Graph( const unsigned nodesNumber, const GraphGenerator * generator ) : start(0), end(nodesNumber - 1), nodesNumber(nodesNumber)
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

const Node & Graph::getNodeStart() const
{
	return nodes[start];
}

const Node & Graph::getNodeEnd() const
{
	return nodes[end];
}

unsigned Graph::getParam( unsigned n, unsigned m, Parameters param ) const
{
	return matrix[ n ][ m ][ (unsigned)param ];
}

void Graph::setEndNodes( unsigned start, unsigned end )
{
	DBG("Graph::setEndNodes( " << start << ", " << end << " )" );

	if( start >= nodesNumber || end >= nodesNumber )
	{
		std::cerr << "Nieprawidłowe dane" << std::endl;
	}

	resetEndNodes();

	this->start = start;

	this->end = end;

	unsigned tmp;

	for(unsigned i = 0; i < nodesNumber; ++i )
	{
		for(unsigned j = 0; j < (unsigned)Parameters::Count; ++j)
		{
			tmp = matrix[ start ][ i ][ j ];
			matrix[ start ][ i ][ j ] = matrix[ 0 ][ i ][ j ];
			matrix[ 0 ][ i ][ j ] = tmp;
		}
	}

	for(unsigned i = 0; i < nodesNumber; ++i )
	{
		for(unsigned j = 0; j < (unsigned)Parameters::Count; ++j)
		{
			tmp = matrix[ i ][ start ][ j ];
			matrix[ i ][ start ][ j ] = matrix[ i ][ 0 ][ j ];
			matrix[ i ][ 0 ][ j ] = tmp;
		}
	}

	for(unsigned i = 0; i < nodesNumber; ++i )
	{
		for(unsigned j = 0; j < (unsigned)Parameters::Count; ++j)
		{
			tmp = matrix[ end ][ i ][ j ];
			matrix[ end ][ i ][ j ] = matrix[ nodesNumber - 1 ][ i ][ j ];
			matrix[ nodesNumber - 1 ][ i ][ j ] = tmp;
		}
	}

	for(unsigned i = 0; i < nodesNumber; ++i )
	{
		for(unsigned j = 0; j < (unsigned)Parameters::Count; ++j)
		{
			tmp = matrix[ i ][ end ][ j ];
			matrix[ i ][ end ][ j ] = matrix[ i ][ nodesNumber - 1 ][ j ];
			matrix[ i ][ nodesNumber - 1 ][ j ] = tmp;
		}
	}
}

void Graph::resetEndNodes()
{
	if( start == 0 && end == nodesNumber - 1 )
		return;

	unsigned tmp;

	for(unsigned i = 0; i < nodesNumber; ++i )
	{
		for(unsigned j = 0; j < (unsigned)Parameters::Count; ++j)
		{
			tmp = matrix[ start ][ i ][ j ];
			matrix[ start ][ i ][ j ] = matrix[ 0 ][ i ][ j ];
			matrix[ 0 ][ i ][ j ] = tmp;
		}
	}

	for(unsigned i = 0; i < nodesNumber; ++i )
	{
		for(unsigned j = 0; j < (unsigned)Parameters::Count; ++j)
		{
			tmp = matrix[ i ][ start ][ j ];
			matrix[ i ][ start ][ j ] = matrix[ i ][ 0 ][ j ];
			matrix[ i ][ 0 ][ j ] = tmp;
		}
	}

	for(unsigned i = 0; i < nodesNumber; ++i )
	{
		for(unsigned j = 0; j < (unsigned)Parameters::Count; ++j)
		{
			tmp = matrix[ end ][ i ][ j ];
			matrix[ end ][ i ][ j ] = matrix[ nodesNumber - 1 ][ i ][ j ];
			matrix[ nodesNumber - 1 ][ i ][ j ] = tmp;
		}
	}

	for(unsigned i = 0; i < nodesNumber; ++i )
	{
		for(unsigned j = 0; j < (unsigned)Parameters::Count; ++j)
		{
			tmp = matrix[ i ][ end ][ j ];
			matrix[ i ][ end ][ j ] = matrix[ i ][ nodesNumber - 1 ][ j ];
			matrix[ i ][ nodesNumber - 1 ][ j ] = tmp;
		}
	}

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
