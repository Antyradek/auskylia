/*  \file   Mutation.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy z klasami mutacji
 */

#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "roll.hpp"

/**
 * \brief Abstrakcyjna klasa bazowa dla klas określających metody mutacji
 */
class Mutation
{
public:
	/**
	 * \brief            operacja mutacji
	 * \param[in] max    maksymalna dopuszczalan wartość
	 * \param[in] min    minimalna dopuszczalna wartość
	 * \param[in] value  wartość modyfikowana
	 * \return           wartośc po mutacji
	 */
	virtual unsigned mutate( unsigned max, unsigned min = 0, unsigned value = 0 ) const = 0;

	/**
	 * \brief szansa na mutację, wyrażona w setnych częściach procenta
	 *        Przykładowo: chance = 200 oznacza 2% szans na mutację
	 */
	unsigned chance;
};

class MutationUniform final : public Mutation
{
	virtual unsigned mutate( unsigned max, unsigned min = 0, unsigned value = 0 )
	{
		if( rollUniform( 1, chance ) == 1 )
			return rollUniform( min, max );
	}
};

class MutationBinomial final : public Mutation
{
	virtual unsigned mutate( unsigned max, unsigned min = 0, unsigned value = 0 )
	{
		if( rollUniform( 1, chance ) == 1 )
			return rollBinomial( value, min, max );
	}
};

#endif // MUTATION_HPP
