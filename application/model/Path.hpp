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

const unsigned NULL_NODE = std::numeric_limits<int>::max();

/**
 * \brief Klasa reprezentujaca ścieżkę w grafie
 */
class Path
{
public:
	Path( unsigned start, unsigned end, unsigned maxLength, const Graph * const graph );

	Path( unsigned * nodes, unsigned length, const Graph * const graph );

	Path( unsigned length, const Graph * const graph );

	~Path();

	unsigned & operator[]( unsigned n ) const;

	bool operator<(const Path & that) const;
	
	unsigned getLength() const;

	unsigned getRating() const;

	void rate();

	void print() const;

private:
	unsigned * path;
	unsigned length;

	unsigned long rating;

	const Graph * const graph;
};

#endif // PATH_HPP
