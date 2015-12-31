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

using AdjacencyMatrix = std::vector< std::vector< std::array< unsigned, (unsigned)Parameters::Count > > >;

using RatingMatrix = std::vector< std::vector< unsigned > >;

/**
 * \brief Abstrakcyjna Klasa bazowa klas generujących grafy
 */
class GraphGenerator
{
public:
	virtual void generate( const unsigned nodes, AdjacencyMatrix & matrix ) const = 0;
};

/**
 * \brief Losuje jednostajnie przedział losowania parametrów
 */
class UniformIntervals : public GraphGenerator
{
public:
	const unsigned INTERVALS_START_MIN = 100;
	const unsigned INTERVALS_START_MAX = 1000;
	const unsigned INTERVALS_SIZE_MIN  = 25;
	const unsigned INTERVALS_SIZE_MAX  = 100;

	virtual void generate( const unsigned nodes, AdjacencyMatrix & matrix ) const;
};

/**
 * \brief losuje wartości parametrów krawędzi, powiększa je o taką samą liczbę i mnoży przez taką samą liczbę
 */
class OtherGenerator : public GraphGenerator
{
public:
	const unsigned MULTIPLIER_MIN = 10;
	const unsigned MULTIPLIER_MAX = 100;
	const unsigned INCREASE_MIN   = 100;
	const unsigned INCREASE_MAX   = 500;
	const unsigned START_MIN      = 20;
	const unsigned START_MAX      = 100;

	virtual void generate( const unsigned nodes, AdjacencyMatrix & matrix ) const;
};

/**
 * \brief Uzależnia parametry od siebie
 */
class SmartGenerator : public GraphGenerator
{
public:

	const unsigned VALUE_MAX = 1000;
	const unsigned VALUE_MIN = 100;

	virtual void generate( const unsigned nodes, AdjacencyMatrix & matrix ) const;
};
