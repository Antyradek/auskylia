/*  \file   Mutation.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy z klasami mutacji
 */

#ifndef MUTATION_HPP
#define MUTATION_HPP

#include "roll.hpp"
#include "Path.hpp"

/**
 * \brief Abstrakcyjna klasa bazowa dla klas określających metody mutacji
 */
class Mutation
{
public:
	Mutation( unsigned chance = 250 ) : chance(chance) {}

	/**
	 * \brief            operacja mutacji
	 * \param[in] max    maksymalna dopuszczalan wartość
	 * \param[in] min    minimalna dopuszczalna wartość
	 * \param[in] value  wartość modyfikowana
	 * \return           wartośc po mutacji
	 */
	virtual unsigned mutate( Path * path, unsigned position, unsigned max, unsigned min, unsigned value ) const = 0;
	
	virtual unsigned mutate( unsigned * path, unsigned position, unsigned max, unsigned min, unsigned value ) const = 0;

	/**
	 * \brief szansa na mutację, wyrażona w setnych częściach procenta
	 *        Przykładowo: chance = 200 oznacza 2% szans na mutację
	 */
	unsigned chance;
};

class MutationUniform final : public Mutation
{
public:
	MutationUniform( unsigned chance = 250) : Mutation( chance ) {}

	virtual unsigned mutate( Path * path, unsigned position, unsigned max, unsigned min, unsigned value ) const
	{
		if( rollUniform( 1, chance ) == 1 )
		{
			unsigned tmp;
			bool done;
			
			do
			{
				done = true;

				tmp = rollUniform( min, max );

				for(unsigned i = 0; i <= position; i++)
					if( tmp == (*path)[i] )
					{
						done = false;
						//break;
					}
			}
			while ( ! done );

			return tmp;
		}

		return value;
	}
	
	virtual unsigned mutate( unsigned * path, unsigned position, unsigned max, unsigned min, unsigned value ) const
	{
		if( rollUniform( 1, chance ) == 1 )
		{
			unsigned tmp;
			bool done;
			
			do
			{
				done = true;

				tmp = rollUniform( min, max );

				for(unsigned i = 0; i <= position; i++)
					if( tmp == path[i] )
					{
						done = false;
						//break;
					}
			}
			while ( ! done );

			return tmp;
		}

		return value;
	}

};

class MutationBinomial final : public Mutation
{
public:
	MutationBinomial( unsigned chance = 250 ) : Mutation( chance ) {}

	virtual unsigned mutate( Path * path, unsigned position, unsigned max, unsigned min, unsigned value ) const
	{
		if( rollUniform( 1, chance ) == 1 )
		{
			unsigned tmp;
			bool done;
			
			do
			{
				done = true;

				tmp = rollBinomial( value, min, max );

				for(unsigned i = 0; i <= position; i++)
					if( tmp == (*path)[i] )
					{
						done = false;
						//break;
					}
			}
			while ( ! done );

			return tmp;
		}

		return value;
	}

	virtual unsigned mutate( unsigned * path, unsigned position, unsigned max, unsigned min, unsigned value ) const
	{
		if( rollUniform( 1, chance ) == 1 )
		{
			unsigned tmp;
			bool done;
			
			do
			{
				done = true;

				tmp = rollBinomial( value, min, max );

				for(unsigned i = 0; i <= position; i++)
					if( tmp == path[i] )
					{
						done = false;
						//break;
					}
			}
			while ( ! done );

			return tmp;
		}

		return value;
	}

};

#endif // MUTATION_HPP
