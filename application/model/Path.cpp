/*  \file   Path.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Path.
 *
 *  \todo   Wyjątki
 */

#include <iostream>       // TODO wywalić po zrobieniu wyjątków
#include <chrono>

#include "Path.hpp"
#include "roll.hpp"

#include "debug.hpp"

Path::Path( unsigned start, unsigned end, unsigned maxLength, const Graph * const graph ) : rating(0), graph(graph)
{
	DBG("Path() new");

	unsigned nodes = graph -> getNodes();
	
	if( maxLength > nodes )
	{
		std::cerr << "[ERR] Path(): maxLength > nodes; maxLength = " << maxLength << ", nodes = " << nodes << std::endl;
		std::cerr << "Commiting sudoku." << std::endl;
		exit(-1);		// TODO - zastąpić wyjątkiem
	}

	if( maxLength < 2 )
	{
		std::cerr << "[ERR] Path(): length < 2; maxLength = " << maxLength << std::endl;
		std::cerr << "Commiting sudoku." << std::endl;
		exit(-1);		// TODO - zastąpić wyjątkiem
	}

	if( start == end )
	{
		std::cerr << "[ERR] Path(): start == end; start = " << start << ", end = " << end << std::endl;
		exit(-1);
	}

	length = rollUniform( 2, maxLength );

	DBG("Path(): length = " << length);

	path = new unsigned [ length ];

	std::vector<unsigned> pool (nodes);

	for(int i = 0; i < nodes; i++)
		pool[i] = i;


	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle (pool.begin(), pool.end(), std::default_random_engine(seed));

	unsigned len = length - 1;
	path[ 0 ] = start;
	path[ len ] = end;

	unsigned j = 0;

	for( unsigned i = 1; i < len; ++i )
	{
		path[ i ] = pool [ i + j ];

		while( path[ i ] == start || path[ i ] == end )
			path[ i ] = pool [ i + ++j ];
	}

	print();
	rate();	
}

Path::Path( unsigned * nodes, unsigned len, const Graph * const graph ) : rating(0), graph(graph)
{
	DBG("Path() from array");
	unsigned count = 0;

	for(int i = 0; i < len; ++i )
		if( nodes[ i ] == NULL_NODE )
		       ++count;	
	
	length = len - count;

	path = new unsigned[length];

	count = 0;

	for(int i = 0; i < len; ++i )
		if( nodes[ i ] == NULL_NODE)
			++count;
		else
			path[ i - count ] = nodes[ i ];

	print();
       rate();	
}


Path::Path( unsigned length, const Graph * const graph ) : length(length), rating(0), graph(graph)
{
	DBG("Path() empty");
	path = new unsigned[length];
}

Path::~Path()
{
	DBG("~Path(" << this << ")");
	delete [] path;
}

unsigned & Path::operator[]( unsigned n ) const
{
	return path[n];
}


bool Path::operator<( const Path & that ) const
{
	return rating < that.getRating();
}

unsigned Path::getLength() const
{
	return length;
}

unsigned Path::getRating() const
{
	return rating;
}

void Path::rate()
{
	DBG("Path::rate()");

	for( int i = 1; i < length; ++i )
		rating += graph->getRating( path[i-1], path[i] );
}

void Path::print() const
{
	std::cout << "Path: [" << rating << "] " << std::endl;

	std::cout << "   ";

	for( int i = 0; i < length; i++)
		std::cout << " "<< path[ i ];

	std::cout << std::endl;
}
