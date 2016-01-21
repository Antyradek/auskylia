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

#include "debug.hpp"

unsigned isqrt(unsigned long value) 
{  
	unsigned result = static_cast<unsigned>(sqrt(static_cast<float>(value)));

	do
		++result;
	while (result * result <= value);
	
	do
		--result;
	while (result * result > value);
	
	return result;  
}

unsigned calcDistance( const Node & first, const Node & second )
{
	unsigned x1 = first.getX();
	unsigned x2 = second.getX();

	unsigned y1 = first.getY();
	unsigned y2 = second.getY();

	unsigned long x = (x1 > x2 ? x1 - x2 : x2 - x1);
	unsigned long y = (y1 > y2 ? y1 - y2 : y2 - y1);

	x *= x;
	y *= y;

	return isqrt( x + y );
}

void GeneratorUniform::generate( std::vector<Node> & nodes, Matrix & matrix ) const
{
	DBG("GeneratorUniform::generate()");

	unsigned nodesNumber = nodes.size();

	rollPoints( nodes );

	unsigned short speed;
	unsigned short safety;
	unsigned short comfort;
	unsigned short cost;
	unsigned distance;

	for( unsigned i = 0; i < nodesNumber; ++i )
		for( unsigned j = 0; j < i; ++j )
		{
			speed = rollUniform( (unsigned)Limits::SPEED_MIN, (unsigned)Limits::SPEED_MAX );

			distance = calcDistance( nodes[i], nodes[j] );

			matrix[ i ][ j ][ (unsigned)Parameters::TIME ] = distance / speed;

			safety = ( nodes[i].getSafety() + nodes[j].getSafety() ) >> 1;
			matrix[ i ][ j ][ (unsigned)Parameters::SAFETY ] = safety;

			comfort = rollUniform( (unsigned)Limits::COMFORT_MIN, (unsigned)Limits::COMFORT_MAX );

			matrix[ i ][ j ][ (unsigned)Parameters::COMFORT ] = comfort;

			cost = ( ( comfort + speed ) >> 1 ) + rollUniform(0, 2) - 1;

			matrix[ i ][ j ][ (unsigned)Parameters::COST ] = distance * cost;

			for( unsigned k = 0; k < (unsigned)Parameters::Count; ++k )
				matrix[ j ][ i ][ k ] = matrix[ i ][ j ][ k ];
		}
}

void GeneratorUniform::rollPoints( std::vector<Node> & nodes ) const
{
	unsigned nodesNumber = nodes.size();

	rollEndPoints( nodes );

	for(unsigned i = 1; i < nodesNumber - 1; ++i)
	{
		nodes[i].roll();

		for(unsigned j = 0; j < i; ++j)
		{
			if( nodes[i].getX() == nodes[j].getX() && nodes[i].getY() == nodes[j].getY() )
			{
				--i;
				break;
			}

			if( nodes[i].getX() == nodes[nodesNumber - 1].getX() && nodes[i].getY() == nodes[ nodesNumber ].getY() )
				--i;
		}	
	}
}	

void GeneratorUniform::rollEndPoints( std::vector<Node> & nodes ) const
{
	nodes[0] = Node( 0, 0 );
	nodes[ nodes.size() - 1 ] = Node( (unsigned)Limits::MAP_SIZE, (unsigned)Limits::MAP_SIZE );
}

