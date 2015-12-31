/*  \file   Path.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Path.
 *
 *  \todo   Wyjątki
 */

#include <limits>

#include <iostream>       // TODO wywalić po zrobieniu wyjątków

#include "Path.hpp"
#include "roll.hpp"

const unsigned NULL_NODE = std::numeric_limits<int>::max();

Path::Path( unsigned start, unsigned end, unsigned maxLength, unsigned nodes )
{
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

	path = new unsigned [ length ];

	bool used[ nodes ];

	unsigned len = length - 1;

	for( unsigned i = 1; i < len; ++i )
		used[ i ] = false;

	path[ 0 ] = start;
	path[ len ] = end;

	used[ start ] = true;
	used[ end ] = true;

	for( unsigned i = 1; i < len; ++i )
	{
		path[ i ] = rollUniform( 0, nodes );

		if( used[ path[ i ] ] == true)
			--i;
		
		else
			used[ path[ i ] ] = true;
	}	
}

Path::Path( unsigned * path, unsigned length ) : length(length)
{
	for(int i = 0; i < length; i++)
		this->path[ i ] = path[ i ]; 
}

Path::~Path()
{
	delete [] path;
}

unsigned Path::operator[]( unsigned n )
{
	return path[n];
}

unsigned Path::getLength()
{
	return length;
}

void Path::print()
{
	std::cout << "Path: [" << length << "] " << std::endl;

	std::cout << "   ";

	for( int i = 0; i < length; i++)
		std::cout << " "<< path[ i ];

	std::cout << std::endl;
}
