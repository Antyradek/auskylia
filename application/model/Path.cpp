/*  \file   Path.hpp
 *
 *  \author Andrzej Roguski
 *
 *  \brief  Plik nagłówkowy klasy Path.
 *
 *  \todo   Wyjątki
 */

#include <iostream>       // TODO wywalić po zrobieniu wyjątków
#include <chrono>

#include "Path.hpp"
#include "roll.hpp"

#include "debug.hpp"

Path::Path( const Graph * const graph, Weights & weights ) : rating(0), graph(graph), weights(weights)
{
	DBG("Path() new");

	unsigned nodes = graph -> getNodes();

	length = rollUniform( 0, nodes - 2 );

	DBG("Path(): length = " << length);

	path = new unsigned [ length ];

	std::vector<unsigned> pool (nodes - 2);

	for(int i = 0; i < nodes - 2; )
		pool[i] = ++i;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle (pool.begin(), pool.end(), std::default_random_engine(seed));

	for( unsigned i = 0; i < length; ++i )
		path[ i ] = pool [ i ];

	DBG_DO( print() );
	rate();	
	DBG_DO(	print() );
}

Path::Path( 
	const Path & first, 
	const Path & second, 
	unsigned end1, 
	unsigned start2, 
	const Graph * const graph, 
	Weights & weights ) 
	: rating(0), graph(graph), weights(weights)
{
	DBG("Path() from others");
	DBG("length1: " << first.getLength() << ", end1: " << end1 << ", length2: " << second.getLength() << ", start2: " << start2 );

	unsigned len1 = end1 + 1;
	unsigned len2 = second.getLength() - start2;

	bool * good = new bool [len1];
	for(int i = 0; i < len1; ++i)
		good[i] = true;

	unsigned badCount = 0;

	for(unsigned i = 0; i <= end1; ++i)
		for(unsigned j = start2; j < second.getLength(); ++j)
			if( first[i] == second[j] )
			{
				good[i] = false;
				++badCount;
				break;
			}

	DBG("BC: " << badCount );

	length = len1 + len2 - badCount;


	DBG("len:" << length );

	path = new unsigned [ length ];

	badCount = 0;

	for( unsigned i = 0; i <= end1; ++i )
		if( good[i] == true )
			path[ i - badCount ] = first[i];
		else
			++badCount;

	DBG_DO( print() );

	for( unsigned i = end1 + 1 - badCount, j = start2; j < second.getLength(); ++i, ++j )
		path[i] = second[j];

	delete [] good;

	DBG_DO(	print() );
}

Path::Path( std::list<unsigned> & list, const Graph * const graph, Weights & weights ) : graph(graph), weights(weights)
{
	length = list.size();

	path = new unsigned [length];

	for( int i = 0; i < length; ++i )
	{
		path[i] = list.front();
		list.pop_front();
	}

	rate();
	DBG_DO( print() );
}

Path::Path( const Path & that ) : graph(that.graph), weights(that.weights), length(that.length), rating(that.rating)
{
	DBG("Patch() copy");

	path = new unsigned [ length ];

	for(int i = 0; i < length; ++i)
		path[i] = that.path[i];
}

Path::~Path()
{
	DBG("~Path(" << this << ")");
	delete [] path;
}

unsigned & Path::operator[]( unsigned n ) const
{
	return path[n];
}


bool Path::operator<( const Path & that ) const
{
	return rating < that.getRating();
}

unsigned Path::getLength() const
{
	return length;
}

unsigned Path::getRating() const
{
	return rating;
}

void Path::rate()
{
	DBG("Path::rate()");

	std::array<unsigned, (unsigned)Parameters::Count> param = {0, 0, 0, 0};
	std::array<unsigned, (unsigned)Parameters::Count> tmpParam;

	unsigned & cost    = param[ (unsigned)Parameters::COST ];
	unsigned & safety  = param[ (unsigned)Parameters::SAFETY ];
	unsigned & comfort = param[ (unsigned)Parameters::COMFORT ];
	unsigned & time    = param[ (unsigned)Parameters::TIME ];

	unsigned & tmpTime    = tmpParam[ (unsigned)Parameters::TIME ];
	unsigned & tmpSafety  = tmpParam[ (unsigned)Parameters::SAFETY ];
	unsigned & tmpComfort = tmpParam[ (unsigned)Parameters::COMFORT ];

	unsigned nodes = graph->getNodes();

	if( length > 0 )
	{
		for( unsigned i = 0; i < length - 1; ++i )
			rateEdge( path[i], path[i+1], param, tmpParam);
		
		rateEdge( 0, path[0], param, tmpParam);
		rateEdge( path[ length - 1 ], nodes - 1, param, tmpParam);
	}
	else
		rateEdge( 0, nodes - 1, param, tmpParam);

	safety /= time;
	comfort /= time;
	unsigned distance = (unsigned)Limits::MAP_SIZE * 1.415;
	unsigned speed = distance / time;

	speed   *= weights[ (unsigned)Parameters::TIME ];
	cost	*= (unsigned)Limits::WEIGHTS_MID;
	cost	*= (unsigned)Limits::WEIGHTS_MID;
	cost    *= weights[ (unsigned)Parameters::COST ];
	comfort *= weights[ (unsigned)Parameters::COMFORT ];
	safety  *= weights[ (unsigned)Parameters::SAFETY ];

	rating = ( distance * speed * comfort - cost ) * safety;

}

inline void Path::rateEdge(
		unsigned one,
		unsigned two,
		std::array<unsigned, (unsigned)Parameters::Count> & param,
		std::array<unsigned, (unsigned)Parameters::Count> & tmpParam)
{
	param[ (unsigned)Parameters::COST ] += graph->getParam( one, two, Parameters::COST );
	
	tmpParam[ (unsigned)Parameters::TIME ] = graph->getParam( one, two, Parameters::TIME );
	param[ (unsigned)Parameters::TIME ] += tmpParam[ (unsigned)Parameters::TIME ];
	
	tmpParam [ (unsigned)Parameters::SAFETY ]= graph->getParam( one, two, Parameters::SAFETY );
	param[ (unsigned)Parameters::SAFETY ] += tmpParam[ (unsigned)Parameters::TIME ] * tmpParam[ (unsigned)Parameters::SAFETY ];

	tmpParam [ (unsigned)Parameters::SAFETY ]= graph->getParam( one, two, Parameters::COMFORT );
	param[ (unsigned)Parameters::COMFORT ] += tmpParam[ (unsigned)Parameters::TIME ] * tmpParam[ (unsigned)Parameters::COMFORT ];	

}

void Path::print() const
{
	std::cout << "Path: [" << rating << "] " << std::endl;

	std::cout << "   ";

	for( int i = 0; i < length; i++)
		std::cout << " "<< path[ i ];

	std::cout << std::endl;
}
