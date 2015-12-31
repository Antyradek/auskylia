/*  \file   Path.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Path.
 */

#ifndef PATH_HPP
#define PATH_HPP

/**
 * \brief Klasa reprezentujaca ścieżkę w grafie
 */

class Path
{
public:
	Path( unsigned start, unsigned end, unsigned maxLength, unsigned nodes );

	Path( unsigned * path, unsigned length );

	~Path();

	unsigned operator[]( unsigned n );

	unsigned getLength();

	void print();

private:
	unsigned * path;
	unsigned length;
};

#endif // PATH_HPP
