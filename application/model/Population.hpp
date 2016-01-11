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
#include "types.hpp"


/**
 * \brief Klasa reprezentująca populację.
 *        Populacja jest związana z konkretnym grafem oraz wierzchołkami początkowym i końcowym.
 */
class Population
{
public:
	/**
	 * \brief            Konstruktor populacji.
	 * \param[in] start  wierzchołek początkowy
	 * \param[in] end    wierzchołek końcowy
	 * \param[in] graph  wskaźnik na graf
	 * \param[in] size   rozmiar populacji, podzielny przez 4 (domyślnie 100)
	 *                   jeśli size nie dzieli się na 4, jest dopełniany do najbliższej czwórki
	 */
	Population( 
		const Graph * const graph, 
		Mutation * mutation, 
		Strategy * strategy, 
		const unsigned size = 100);

	/**
	 * \brief               Jedna iteracja krzyżowania.
	 * \paran[in] strategy  wskaźnik na strategię doboru osobników w pary
	 * \param[in] mutation  wskaźnik na obiekt z algorytmem mutacji
	 */
	void evolve();

	/**
	 * \brief      
	 * \param[in]  wskaźnik na pierwszego rodzica
	 * \param[in]  wskaźnik na drugiego rodzica
	 * \param[out] referencja do wskaźnika na pierwszego potomka
	 * \param[out] referencja do wskaźnika na drugiego potomka
	 */
	void newPaths ( Path * in1, Path * in2, Path * & out1, Path * & out2 );

	/**
	 * \brief        Zwraca wskaźnik na n-tą najlepszą ścieżkę.
	 * \param[in] n  numer ściezki
	 */
	Path * getPath( const unsigned n = 0 ) const;

	void setStrategy( Strategy * strategy );

	void setMutation( Mutation * mutation );

	void setWeights( const Weights & arr );

	/**
	 * \brief  Wypisuje populację.
	 */
	void print();

private:
	std::vector<Path *> paths;

	Weights weights;

	const unsigned size;

	Mutation * mutation;

	Strategy * strategy;

	const Graph * const graph;

	const unsigned nodes;

	bool isInPopulation( Path * path ) const;
};

#endif // POPULATION_HPP

