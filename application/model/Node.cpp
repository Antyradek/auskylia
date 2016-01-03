/** 
 *  \file   Graph.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Graph.
 */

#include <iostream>

#include "Node.hpp"
#include "roll.hpp"
#include "parameters.hpp"


Node::Node()
{

	safety = rollUniform( (unsigned)Limits::SAFETY_MIN, (unsigned)Limits::SAFETY_MAX );
}

Node::Node( unsigned x, unsigned y) : x(x), y(y)
{	
	safety = rollUniform( (unsigned)Limits::SAFETY_MIN, (unsigned)Limits::SAFETY_MAX );
}

Node::~Node()
{

}

void Node::roll()
{
	x = rollUniform( 1, (unsigned)Limits::MAP_SIZE );

	y = rollUniform( 1, (unsigned)Limits::MAP_SIZE );
}

unsigned Node::getX() const
{
	return x;
}

unsigned Node::getY() const
{
	return y;
}

unsigned Node::getSafety() const
{
	return safety;
}

void Node::print() const
{
	std::cout << "(" << x << ", " << y << ")";
}
