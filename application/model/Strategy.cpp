/** 
 *  \file Strategy.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief Plik z definicjami startegii krzyżowania.
*/

#include <vector>

#include "strategy.hpp"

void StrategyClosest::match( const std::vector<Path *> & in, std::vector<Path *> & out1, std::vector<Path *> & out2, const unsigned size ) const
{
	for(int i = 0; i < size; i++)
	{
		out1[i] = in[2*i];
		out2[i] = in[2*i + 1];
	}
}
