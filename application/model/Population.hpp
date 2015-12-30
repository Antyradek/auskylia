/** 
 *  \file Population.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief Plik nagłówkowy klasy Population.
 */

#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Mutation.hpp"
#include "strategy.hpp"
#include "Path.hpp"

/**
 * \brief Klasa reprezentująca populację.
 */

class Population
{
public:
	Population( unsigned size = 100 );

	void evolve( const Strategy & strategy, const Mutation & mutation );

	Path * getPath( unsigned n = 0 );

private:
	Path paths[];

	unsigned size;
};

#endif // POPULATION_HPP

