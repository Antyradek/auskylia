/** 
 *  \file Population.cpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief Definicja klasy Population.
 */
#include <algorithm>
#include <iostream>

#include "Population.hpp"
#include "roll.hpp"

#include "debug.hpp"

struct pathPtrCompr
{
	bool operator()(const Path * l, const Path * r)
	{
		return *l < *r;
	}
};

Population::Population( 
		const Graph * const graph, 
		Mutation * mutation, 
		Strategy * strategy, 
		const unsigned size )
	: size(size), strategy(strategy), mutation(mutation), graph(graph), nodes( graph->getNodes() )
{
	DBG("Population()");

	for(unsigned i : weights)
		i = (unsigned)Limits::WEIGHTS_MID;

	paths = std::vector<Path*> (size);

	for( unsigned i = 0; i < size; i++)
		paths[i] = new Path( graph, weights );

	std::sort( paths.begin(), paths.end(), pathPtrCompr() );
}

void Population::evolve()
{
	DBG("Population::evolve()");

	std::vector<Path *> out1 (size/4);
	std::vector<Path *> out2 (size/4);


	strategy -> match( paths, out1, out2, size/4 );

	unsigned half = size>>1;

	for(int i = 0; i < half>>1; ++i)
	{
		delete paths[half + 2*i];
		delete paths[half + 2*i + 1];
		newPaths( out1[i], out2[i], paths[half + 2*i], paths[half + 2*i + 1] );
	}

	std::sort( paths.begin(), paths.end(), pathPtrCompr() );	
}

void Population::newPaths ( Path * in1, Path * in2, Path * & out1, Path * & out2 )
{
	DBG("Population::newPaths()");

	DBG("Source paths:");
	DBG_DO( in1->print() );
	DBG_DO( in2->print() );

	if( in1 -> getLength() < 2 || in2 -> getLength() < 2)
	{
		out1 = new Path(*in1);
		out2 = new Path(*in2);
	}

	else
	{
		unsigned cut1 = rollUniform( 0, in1 -> getLength() - 2 );
		unsigned cut2 = rollUniform( 0, in2 -> getLength() - 2 );

		out1 = new Path( *in1, *in2, cut1, cut2 + 1, graph, weights );
		out2 = new Path( *in2, *in1, cut2, cut1 + 1, graph, weights );
	}
}

Path * Population::getPath( unsigned n ) const
{
	return paths[n];
}

void Population::setStrategy( Strategy * strategy )
{
	this->strategy = strategy;
}

void Population::setMutation( Mutation * mutation )
{
	this->mutation = mutation;
}

void Population::setWeights( std::array<unsigned, (unsigned)Parameters::Count> arr )
{
	unsigned size = arr.size();
	for(unsigned i = 0; i < size; ++i )
		i = arr[i];
}

void Population::print()
{
	std::cout << "Number of paths: " << size << std::endl;  

	unsigned i = 0;

	for (auto p : paths)
	{
		std::cout << "<" << i++ << "> ";
		p->print();
	}
}
