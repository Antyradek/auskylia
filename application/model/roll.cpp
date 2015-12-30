#include "roll.hpp"

unsigned rollUniform( unsigned min, unsigned max )
{
	if( max < min)
		exit(-1);                              // TODO zamienić na wyjątek

	static std::random_device rdev{};
	static std::default_random_engine e{rdev()};
	
	std::uniform_int_distribution<unsigned> d(min, max);

	return d(e);
}

unsigned rollBinomial( unsigned value, unsigned min, unsigned max )
{
	if( max < min || max < value || value < min)
		exit(-1);                              // TODO zamienić na wyjątek

	static std::random_device rdev{};
	static std::default_random_engine e{rdev()};
	
	unsigned maxRoll;
	unsigned shift;
	unsigned result;

	if( max - value > value - min )
	{
		maxRoll = 2 * (max - value);
		shift = 2 * value - max;
	}

	else
	{
		maxRoll = 2 * (value - min);
		shift = min;
	}

	std::binomial_distribution<unsigned> d( maxRoll, 0.5);
	
	do
	{
		result = d(e) + shift;
	}
	while ( result > max || result < min );

	return result;
}


