/** 
 *  \file   GraphGenerator.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy GraphGenerator.
 */

#include <vector>
#include <array>

#include "parameters.hpp"
#include "Node.hpp"
#include "types.hpp"
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
	unsigned calcDistance( const Node & first, const Node & second ) const;
	void rollEndPoints( std::vector<Node> & nodes ) const;
};
