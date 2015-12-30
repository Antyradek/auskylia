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
	if( maxLength > nodes - 2 )
	{
		std::cerr << "[ERR] Path(): maxLength > nodes - 2; maxLength = " << maxLength << ", nodes = " << nodes << std::endl;
		std::cerr << "Commiting sudoku." << std::endl;
		exit(-1);		// TODO - zastąpić wyjątkiem
	}

	length = rollUniform( 1, maxLength );

	path = new unsigned [ length ];

	bool used[ nodes ];

	for( unsigned i = 0; i < length; ++i )
		used[ i ] = false;

	for( unsigned i = 0; i < length; ++i )
	{
		path[ i ] = rollUniform( 0, nodes );

		if( path[ i ] == end || path[ i ] == start || used[ path[ i ] ] == true)
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
