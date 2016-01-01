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
		const unsigned start, 
		const unsigned end, 
		const Graph * const graph, 
		Mutation * mutation, 
		Strategy * strategy, 
		const unsigned size )
	: size(size), start(start), end(end), strategy(strategy), mutation(mutation), graph(graph), nodes( graph->getNodes() )
{
	DBG("Population()");

	paths = std::vector<Path*> (size);

	for( unsigned i = 0; i < size; i++)
		paths[i] = new Path( start, end, nodes, graph );

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

	unsigned len1 = in1 -> getLength();
	unsigned len2 = in2 -> getLength();
	
	unsigned length;


	if( len1 == len2 )
	{
		length = len1;

		out1 = new Path(length, graph);
		out2 = new Path(length, graph);

		bool choice;
		
		(*out1)[0] = start;
		(*out2)[0] = start;

		(*out1)[length - 1] = end;
		(*out2)[length - 1] = end;
		
		for( int i = 1; i < length - 1; ++i )
		{
			choice = rollBinary();
			
			if(choice)
			{
				(*out1)[i] = mutation->mutate( start, end, nodes - 1, 0, (*in1)[i] );
				(*out2)[i] = mutation->mutate( start, end, nodes - 1, 0, (*in2)[i] );	
			}	
			else
			{
				(*out1)[i] = mutation->mutate( start, end, nodes - 1, 0, (*in2)[i] );
				(*out2)[i] = mutation->mutate( start, end, nodes - 1, 0, (*in1)[i] );	
			}
		}

		out1 -> rate();
		out2 -> rate();
	}

	else
	{
		unsigned difference;
		Path * shorter;
		Path * longer;

		if( len1 > len2 )
		{
			length = len1;
			difference = length - len2;
			longer = in1;
			shorter = in2;
		}
		else
		{
			length = len2;
			difference = length - len1;
			longer = in2;
			shorter = in1;
		}


		unsigned newIn[length];

		for(unsigned i = 0; i < length; ++i)
			newIn[i] = 0;

		unsigned n;

		for(unsigned i = 0; i < difference; ++i)
		{
			n = rollUniform(1, length - 2);

			if( newIn[ n ] == NULL_NODE )
				--i;
			else
				newIn[ n ] = NULL_NODE;
		}

		for( unsigned i = 0, j = 0; i < length; ++i, ++j )
		{
			if( newIn[ i ] == NULL_NODE )
				--j;
			else
				newIn[ i ] = (*shorter)[ j ];
		}


		unsigned rawOut1 [length];
		unsigned rawOut2 [length];

		bool choice;

		rawOut1[0] = start;
		rawOut2[0] = start;

		rawOut1[length - 1] = end;
		rawOut2[length - 1] = end;

		for( int i = 1; i < length-1; ++i )
			{
				choice = rollBinary();
				
				if(choice)
				{
					rawOut1[i] = mutation->mutate( start, end, nodes - 1, 0, newIn[i] );
					rawOut2[i] = mutation->mutate( start, end, nodes - 1, 0, (*longer)[i] );	
				}	
				else
				{
					rawOut1[i] = mutation->mutate( start, end, nodes - 1, 0, (*longer)[i] );
					rawOut2[i] = mutation->mutate( start, end, nodes - 1, 0, newIn[i] );	
				}
			}
		
		out1 = new Path(rawOut1, length, graph);
		out2 = new Path(rawOut2, length, graph);

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
