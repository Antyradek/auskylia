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

Population::Population( const unsigned start, const unsigned end, const Graph * const graph, const unsigned size )
	: size(size), start(start), end(end), graph(graph)
{
	DBG("Population()");

	unsigned nodes = graph->getNodes();

	paths = std::vector<Path*> (size);

	for( unsigned i = 0; i < size; i++)
		paths[i] = new Path( start, end, nodes, graph );

	std::sort( paths.begin(), paths.end(), pathPtrCompr() );
}

void Population::evolve( const Strategy * strategy, const Mutation * mutation )
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
		for( int i = 0; i < length; ++i )
		{
			choice = rollBinary();
			
			if(choice)
			{
				(*out1)[i] = (*in1)[i];
				(*out2)[i] = (*in2)[i];	
			}	
			else
			{
				(*out1)[i] = (*in2)[i];
				(*out2)[i] = (*in1)[i];	
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

		if( in1 -> getLength() > in2 -> getLength() )
		{
			length = in1 -> getLength();
			difference = length - in2 -> getLength();
			longer = in1;
			shorter = in2;
		}
		else
		{
			length = in2 -> getLength();
			difference = length - in1 -> getLength();
			longer = in2;
			shorter = in1;
		}

		unsigned newIn[length];

		for(unsigned i = 0; i < length; ++i)
			newIn[i] = 0;

		unsigned n;

		for(unsigned i = 0; i < difference; ++i)
		{
			n = rollUniform(0, length - 1);

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
		for( int i = 0; i < length; ++i )
			{
				choice = rollBinary();
				
				if(choice)
				{
					rawOut1[i] = newIn[i];
					rawOut2[i] = (*longer)[i];	
				}	
				else
				{
					rawOut1[i] = (*longer)[i];
					rawOut2[i] = newIn[i];	
				}
			}
		
		out1 = new Path(rawOut1, length, graph);
		out2 = new Path(rawOut2, length, graph);

	}

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
