/*  \file   Mutation.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy z klasami mutacji
 */

#ifndef MUTATION_HPP
#define MUTATION_HPP

#include <list>

#include "roll.hpp"
#include "Path.hpp"

#include "debug.hpp"

/**
 * \brief Abstrakcyjna klasa bazowa dla klas określających metody mutacji
 */
class Mutation
{
public:
	Mutation( unsigned chance = 250 ) : chance(chance) {}

	virtual void mutate( const Path & path, std::list<unsigned> & list, unsigned nodes ) const = 0;

	/**
	 * \brief szansa na mutację, wyrażona w setnych częściach procenta
	 *        Przykładowo: chance = 200 oznacza 2% szans na mutację
	 */
	unsigned chance;
};

class MutationUniform final : public Mutation
{
public:
	MutationUniform( unsigned chance = 500 ) : Mutation( chance ) {}

	virtual void mutate( const Path & path, std::list<unsigned> & list, unsigned nodes ) const
	{
		DBG("MutationUnifor::mutate()");
		unsigned tmp;

		for(unsigned i = 0; i < path.getLength(); ++i )
			list.push_back(i);

		for(std::list<unsigned>::iterator i = list.begin(); i != list.end(); ++i )
			if( rollUniform( 1, 10000 ) <= chance )
			{
				switch( rollUniform( 1, 3 ) )
				{
					case 1:
						tmp = rollUniform( 1, nodes - 2 );

						if( ! isInPath( path, tmp) )
						{
							i = list.erase(i);
							list.insert(i, tmp);
						}
						break;
					case 2:
						i = list.erase(i);
						break;
					case 3:
						tmp = rollUniform( 1, nodes - 2);

						if( ! isInPath(path, tmp) )
						{
							list.insert(i, tmp);
						}
						break;
				};	
			}
	}

private:
	bool isInPath( const Path & path, unsigned node ) const
	{
		for( int j = 0; j < path.getLength(); ++j )
			if( node == path[j] )
				return true;

		return false;
	}

};

class MutationBinomial final : public Mutation
{
public:

};

#endif // MUTATION_HPP
