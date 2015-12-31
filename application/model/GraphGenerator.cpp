/** 
 *  \file   GraphGenerator.cpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Definicja klasy GraphGenerator.
 */

#include "parameters.hpp"
#include "roll.hpp"
#include "GraphGenerator.hpp"

void UniformIntervals::generate( const unsigned nodes, AdjacencyMatrix & matrix ) const
{
	unsigned intervalStart;
	unsigned intervalSize;

	matrix = AdjacencyMatrix(nodes, std::vector<std::array< unsigned, (unsigned)Parameters::Count > >(nodes));



	for( unsigned i = 0; i < nodes; i++ )
		for( unsigned j = 0; j < i; j++ )
		{
			if( i == j )
				continue;

			intervalStart = rollUniform( INTERVALS_START_MIN, INTERVALS_START_MAX );
			intervalSize = rollUniform( INTERVALS_SIZE_MIN, INTERVALS_SIZE_MAX );
			
			for( unsigned k = 0; k < (unsigned)Parameters::Count; k++ )
			{
				matrix[ i ][ j ][ k ] = rollUniform( intervalStart, intervalStart + intervalSize );
				matrix[ j ][ i ][ k ] = matrix[ i ][ j ][ k ];
			}
		}
}

void OtherGenerator::generate( const unsigned nodes, AdjacencyMatrix & matrix ) const
{
	unsigned startValue;
	unsigned multiplier;
	unsigned increase;

	matrix = AdjacencyMatrix(nodes, std::vector<std::array< unsigned, (unsigned)Parameters::Count > >(nodes));


	for( unsigned i = 0; i < nodes; i++ )
		for( unsigned j = 0; j < i; j++ )
		{
			if( i == j )
				continue;

			multiplier = rollUniform( MULTIPLIER_MIN, MULTIPLIER_MAX );
			increase = rollUniform( INCREASE_MIN, INCREASE_MAX );
			
			for( unsigned k = 0; k < (unsigned)Parameters::Count; k++ )
			{
				matrix[ i ][ j ][ k ] = rollUniform( START_MIN, START_MAX );
				
				matrix[ i ][ j ][ k ] += increase;
				matrix[ i ][ j ][ k ] *= multiplier;

				matrix[ j ][ i ][ k ] = matrix[ i ][ j ][ k ];
			}
		}
}

void SmartGenerator::generate( const unsigned nodes, AdjacencyMatrix & matrix ) const
{
	matrix = AdjacencyMatrix(nodes, std::vector<std::array< unsigned, (unsigned)Parameters::Count > >(nodes));

	unsigned security;
	unsigned comfort;
	unsigned time;
	unsigned cost;
	unsigned tmp;

	for( unsigned i = 0; i < nodes; i++ )
		for( unsigned j = 0; j < i; j++ )
		{
			if( i == j )
				continue;
			
			time = rollUniform( VALUE_MIN, VALUE_MAX );
			comfort = rollUniform( VALUE_MIN, VALUE_MAX );
			
			matrix[ i ][ j ][ (unsigned)Parameters::TIME ] = time;
			matrix[ i ][ j ][ (unsigned)Parameters::COMFORT ] = comfort;
			
			security = rollUniform( VALUE_MIN, VALUE_MAX );
			tmp = (VALUE_MAX - comfort) / 5;

			if( security - VALUE_MIN > tmp )
				security -= tmp;
			else
				security = VALUE_MIN;

			tmp = (VALUE_MAX - comfort) / 10;

			if( tmp > 40)
				cost = rollUniform( tmp - 30, tmp + 30 );
			else
				cost = rollUniform( 10, tmp + 30 );

			cost *= (time / 100);

			
			matrix[ i ][ j ][ (unsigned)Parameters::TIME ] = time;
			matrix[ i ][ j ][ (unsigned)Parameters::COMFORT ] = comfort;
			matrix[ i ][ j ][ (unsigned)Parameters::SECURITY ] = security;
			matrix[ i ][ j ][ (unsigned)Parameters::COST ] = cost;

			for( unsigned k = 0; k < (unsigned)Parameters::Count; k++ )
				matrix[ j ][ i ][ k ] = matrix[ i ][ j ][ k ];
		}
}
