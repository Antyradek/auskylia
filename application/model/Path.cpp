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
#include "GraphGenerator.hpp"

#include "debug.hpp"

Path::Path( const Graph * const graph, Weights & weights ) : rating(0), graph(graph), weights(weights)
{
	DBG("Path() new");

	unsigned nodes = graph -> getNodes();

	static unsigned nodesSqrt = isqrt( nodes );

	length = rollBinomialUltraWide( nodesSqrt, 0, nodes - 2 );

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

double Path::getRating() const
{
	return rating;
}

void Path::rate()
{
	DBG("Path::rate()");

	std::array<unsigned long, (unsigned)Parameters::Count> param = {0, 0, 0, 0};
	std::array<unsigned long, (unsigned)Parameters::Count> tmpParam;

	unsigned long & cost    = param[ (unsigned)Parameters::COST ];
	unsigned long & safety  = param[ (unsigned)Parameters::SAFETY ];
	unsigned long & comfort = param[ (unsigned)Parameters::COMFORT ];
	unsigned long & time    = param[ (unsigned)Parameters::TIME ];

	unsigned long & tmpTime    = tmpParam[ (unsigned)Parameters::TIME ];
	unsigned long & tmpSafety  = tmpParam[ (unsigned)Parameters::SAFETY ];
	unsigned long & tmpComfort = tmpParam[ (unsigned)Parameters::COMFORT ];

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

	double saf = (double)safety / time;
	double com = (double)comfort / time;
	double distance = (unsigned)Limits::MAP_SIZE * 1.415;
	double speed = distance / time;

	DBG(" " << weights[0] << " " << weights[1] << " " << weights[2] << " " << weights[3]  );
	
	speed   *= weights[ (unsigned)Parameters::TIME ];
	cost    *= weights[ (unsigned)Parameters::COST ];
	com     *= weights[ (unsigned)Parameters::COMFORT ];
	saf     *= weights[ (unsigned)Parameters::SAFETY ];

	DBG("d " << distance << " s " << speed << " c " << com << " $ " << cost << " sa " << saf );

	rating = ( distance * speed * com - cost ) * saf;

}

inline void Path::rateEdge(
		unsigned one,
		unsigned two,
		std::array<unsigned long, (unsigned)Parameters::Count> & param,
		std::array<unsigned long, (unsigned)Parameters::Count> & tmpParam)
{
	param[ (unsigned)Parameters::COST ] += graph->getParam( one, two, Parameters::COST );
	
	tmpParam[ (unsigned)Parameters::TIME ] = graph->getParam( one, two, Parameters::TIME );
	param[ (unsigned)Parameters::TIME ] += tmpParam[ (unsigned)Parameters::TIME ];
	
	tmpParam [ (unsigned)Parameters::SAFETY ]= graph->getParam( one, two, Parameters::SAFETY );
	param[ (unsigned)Parameters::SAFETY ] += tmpParam[ (unsigned)Parameters::TIME ] * tmpParam[ (unsigned)Parameters::SAFETY ];

	tmpParam [ (unsigned)Parameters::COMFORT ]= graph->getParam( one, two, Parameters::COMFORT );
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
