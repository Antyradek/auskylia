/*  \file   Path.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Path.
 */

#ifndef PATH_HPP
#define PATH_HPP

#include <limits>

#include "Graph.hpp"
#include "types.hpp"

const unsigned NULL_NODE = std::numeric_limits<int>::max();

/**
 * \brief Klasa reprezentujaca ścieżkę w grafie
 */
class Path
{
public:
	Path( const Graph * const graph, const Weights & weights );

	Path( const Path & first, const Path & second, unsigned end1, unsigned start2, const Graph * const graph, const Weights & weights );

	Path( const Path & that );

	~Path();

	unsigned & operator[]( unsigned n ) const;

	bool operator<(const Path & that) const;
	
	unsigned getLength() const;

	unsigned getRating() const;

	void rate();

	inline void rateEdge(
		unsigned one,
		unsigned two,
		std::array<unsigned, (unsigned)Parameters::Count> & param,
		std::array<unsigned, (unsigned)Parameters::Count> & tmpParam);


	void print() const;

private:
	unsigned * path;
	unsigned length;

	unsigned long rating;

	const Weights & weights;

	const Graph * const graph;
};

#endif // PATH_HPP
