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
		return *r < *l;
	}
};

Population::Population( 
		const Graph * const graph, 
		Mutation * mutation, 
		Strategy * strategy, 
		const unsigned size )
	: size(size), mutation(mutation), strategy(strategy), graph(graph), nodes( graph->getNodes() )
{
	DBG("Population()");

	for( unsigned i = 0; i < (unsigned)Parameters::Count; ++i )
		weights[i] = 50;

	paths = std::vector<Path*> (size);

	for( unsigned i = 0; i < size; i++)
		paths[i] = new Path( graph, weights );

	std::sort( paths.begin(), paths.end(), pathPtrCompr() );
}

Population::~Population()
{
	for( auto p : paths )
		delete p;
}

void Population::evolve()
{
	DBG("Population::evolve()");

	std::vector<Path *> out1 (size/4);
	std::vector<Path *> out2 (size/4);


	strategy -> match( paths, out1, out2, size/4 );

	unsigned half = size>>1;

	for( unsigned i = 0; i < half>>1; ++i)
	{
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

	if( in1 -> getLength() < 3 || in2 -> getLength() < 3)
	{
		do
		{
			delete out1;
			out1 = new Path( graph, weights );
		}
		while( isInPopulation( out1 ) );

		do
		{
			delete out2;
			out2 = new Path( graph, weights );
		}
		while( isInPopulation(out2) );
	}

	else
	{
		delete out1;
		delete out2;

		unsigned cut1 = rollUniform( 0, in1 -> getLength() - 2 );
		unsigned cut2 = rollUniform( 0, in2 -> getLength() - 2 );

		Path tmp1 ( *in1, *in2, cut1, cut2 + 1, graph, weights );
		Path tmp2 ( *in2, *in1, cut2, cut1 + 1, graph, weights );

		std::list<unsigned> list1;
		std::list<unsigned> list2;

		mutation->mutate( tmp1, list1, nodes );
		mutation->mutate( tmp2, list2, nodes );
		
		out1 = new Path( list1, graph, weights );
		while( isInPopulation( out1 ) )
		{
			delete out1;
			out1 = new Path( graph, weights );
		}

		out2 = new Path( list2, graph, weights );
		while( isInPopulation( out2 ) )
		{
			delete out2;
			out2 = new Path( graph, weights );
		}
	}
}

bool Population::isInPopulation( Path * path ) const
{
	unsigned i = 0;
	while( paths[i] != path )
		if( *paths[i++] == *path )
			return true;

	return false;
}

Path * Population::getPath( unsigned n ) const
{
	return paths[n];
}

unsigned Population::getSize() const
{
	return size;
}

Strategy * Population::getStrategy() const
{
	return strategy;
}

Mutation * Population::getMutation() const
{
	return mutation;
}

void Population::setStrategy( Strategy * strategy )
{
	this->strategy = strategy;
}

void Population::setMutation( Mutation * mutation )
{
	this->mutation = mutation;
}

void Population::setWeights( const Weights & arr )
{
	unsigned size = arr.size();
	for(unsigned i = 0; i < size; ++i )
		weights[i] = arr[i];

	for( Path * p : paths )
		p -> rate();

	std::sort( paths.begin(), paths.end(), pathPtrCompr() );	
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
