/** 
 *  \file   GraphGenerator.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy GraphGenerator.
 */

#ifndef GRAPH_GENERATOR_HPP
#define GRAPH_GENERATOR_HPP

#include <cmath>
#include <vector>
#include <array>

#include "parameters.hpp"
#include "Node.hpp"
#include "types.hpp"


unsigned isqrt(unsigned long value); 

unsigned calcDistance( const Node & first, const Node & second );

/**
 * \brief Abstrakcyjna Klasa bazowa klas generujących grafy
 */
class GraphGenerator
{
public:
	virtual void generate( std::vector<Node> & nodes, Matrix & matrix ) const = 0;
};


class GeneratorUniform : public GraphGenerator
{
public:	
	virtual void generate( std::vector<Node> & nodes, Matrix & matrix ) const;

private:
	void rollPoints( std::vector<Node> & nodes ) const;
	void rollEndPoints( std::vector<Node> & nodes ) const;
};

#endif // GRAPH_GENERATOR_HPP
