/** 
 *  \file Population.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief Plik nagłówkowy klasy Population.
 */

#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <array>

#include "Mutation.hpp"
#include "strategy.hpp"
#include "Path.hpp"

/**
 * \brief Klasa reprezentująca populację.
 */

class Population
{
public:
	Population( const unsigned start, const unsigned end, const Graph * const graph, const unsigned size = 100 );

	void evolve( const Strategy * strategy, const Mutation * mutation );

	void newPaths ( Path * in1, Path * in2, Path * & out1, Path * & out2 );

	Path * getPath( const unsigned n = 0 ) const;

	void print();

private:
	std::vector<Path *> paths;

	const unsigned size;

	const unsigned start;

	const unsigned end;

	const Graph * const graph;
};

#endif // POPULATION_HPP

