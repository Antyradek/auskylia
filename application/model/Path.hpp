/*  \file   Path.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Path.
 */

#ifndef PATH_HPP
#define PATH_HPP

#include <limits>
#include <list>

#include "Graph.hpp"
#include "types.hpp"

const unsigned NULL_NODE = std::numeric_limits<int>::max();

/**
 * \brief Klasa reprezentujaca ścieżkę w grafie
 */
class Path
{
public:
	Path( const Graph * const graph, Weights & weights );

	Path( const Path & first, const Path & second, unsigned end1, unsigned start2, const Graph * const graph, Weights & weights );

	Path( const Path & that );
	
	Path( std::list<unsigned> & list, const Graph * const graph, Weights & weights );
	
	~Path();

	unsigned & operator[]( unsigned n ) const;

	bool operator<(const Path & that) const;

	bool operator==(const Path & that) const;
	
	unsigned getLength() const;

	double getRating() const;

	double getParam( Parameters p ) const;

	void rate();

	inline void rateEdge(
		unsigned one,
		unsigned two,
		std::array<unsigned long, (unsigned)Parameters::Count> & param,
		std::array<unsigned long, (unsigned)Parameters::Count> & tmpParam);


	void print() const;

private:
	unsigned * path;
	unsigned length;

	double * params;

	double rating;

	Weights & weights;

	const Graph * const graph;
};

#endif // PATH_HPP
