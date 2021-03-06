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

Path::Path( const Graph * const graph, Weights & weights ) : rating(0), weights(weights), graph(graph)
{
	DBG("Path() new");

	params = new double[ Parameters::Count ];

	for(unsigned i = 0; i < (unsigned)Parameters::Count; ++i)
		params[ i ] = 0;

	unsigned nodes = graph -> getNodes();

	static unsigned nodesSqrt = isqrt( nodes );

	length = rollBinomialUltraWide( nodesSqrt, 0, nodes - 2 );

	DBG("Path(): length = " << length);

	path = new unsigned [ length ];

	std::vector<unsigned> pool (nodes - 2);

	for( unsigned i = 0; i < nodes - 2; ++i )
		pool[i] = i + 1;

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
	: rating(0), weights(weights), graph(graph)
{
	DBG("Path() from others");
	DBG("length1: " << first.getLength() << ", end1: " << end1 << ", length2: " << second.getLength() << ", start2: " << start2 );

	params = new double[ Parameters::Count ];

	for(unsigned i = 0; i < (unsigned)Parameters::Count; ++i)
		params[ i ] = 0;

	unsigned len1 = end1 + 1;
	unsigned len2 = second.getLength() - start2;

	bool * good = new bool [len1];
	for( unsigned i = 0; i < len1; ++i )
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

	rate();
}

Path::Path( std::list<unsigned> & list, const Graph * const graph, Weights & weights ) : weights(weights), graph(graph)
{
	params = new double[ Parameters::Count ];

	for(unsigned i = 0; i < (unsigned)Parameters::Count; ++i)
		params[ i ] = 0;

	length = list.size();

	path = new unsigned [length];

	for( unsigned i = 0; i < length; ++i )
	{
		path[i] = list.front();
		list.pop_front();
	}

	rate();
	DBG_DO( print() );
}

Path::Path( const Path & that ) : length(that.length), rating(that.rating), weights(that.weights), graph(that.graph)
{
	DBG("Patch() copy");
	
	params = new double[ Parameters::Count ];

	for(unsigned i = 0; i < (unsigned)Parameters::Count; ++i)
		params[ i ] = that.params[ i ];

	path = new unsigned [ length ];

	for( unsigned i = 0; i < length; ++i)
		path[i] = that.path[i];
}

Path::~Path()
{
	DBG("~Path(" << this << ")");
	delete [] path;
	delete [] params;
}

unsigned & Path::operator[]( unsigned n ) const
{
	return path[n];
}


bool Path::operator<( const Path & that ) const
{
	return rating < that.getRating();
}

bool Path::operator==( const Path & that ) const
{
	if( this->length != that.length )
		return false;

	if( this->rating != that.rating )
		return false;

	for( unsigned i = 0; i < length; ++i )
		if( this->path[i] != that.path[i] )
			return false;

	return true;
}

unsigned Path::getLength() const
{
	return length;
}

double Path::getRating() const
{
	return rating;
}

double Path::getParam( Parameters p ) const
{
	return params[ (unsigned)p ];
}

void Path::rate()
{
	DBG("Path::rate()");

	std::array<unsigned long, (unsigned)Parameters::Count> param = {0, 0, 0, 0};

	unsigned long & cost    = param[ (unsigned)Parameters::COST ];
	unsigned long & safety  = param[ (unsigned)Parameters::SAFETY ];
	unsigned long & comfort = param[ (unsigned)Parameters::COMFORT ];
	unsigned long & time    = param[ (unsigned)Parameters::TIME ];

	unsigned nodes = graph->getNodes();

	if( length > 0 )
	{
		for( unsigned i = 0; i < length - 1; ++i )
			rateEdge( path[i], path[i+1], param );
		
		rateEdge( 0, path[0], param );
		rateEdge( path[ length - 1 ], nodes - 1, param );
	}
	else
		rateEdge( 0, nodes - 1, param );

	double saf = (double)safety / (double)time;
	double com = (double)comfort / (double)time;

	double distance = calcDistance( graph->getNodeStart(), graph->getNodeEnd() );
	double speed = distance / time;

	DBG(" " << weights[0] << " " << weights[1] << " " << weights[2] << " " << weights[3]  );
	
	params[ (unsigned)Parameters::TIME ] = time;
	params[ (unsigned)Parameters::COST ] = cost;
	params[ (unsigned)Parameters::COMFORT ] = com;
	params[ (unsigned)Parameters::SAFETY ] = saf;

	speed   *= weights[ (unsigned)Parameters::TIME ];
	cost    *= weights[ (unsigned)Parameters::COST ];
	com     *= weights[ (unsigned)Parameters::COMFORT ];
	saf     *= weights[ (unsigned)Parameters::SAFETY ];

	DBG("d " << distance << " s " << speed << " c " << com << " $ " << cost << " sa " << saf );

	rating = speed + com + saf - (double)cost/distance;

}

inline void Path::rateEdge(
		unsigned one,
		unsigned two,
		std::array<unsigned long, (unsigned)Parameters::Count> & param)
{
	std::array<unsigned long, (unsigned)Parameters::Count> tmpParam;
	
	tmpParam[ (unsigned)Parameters::TIME ]     = graph->getParam( one, two, Parameters::TIME );
	tmpParam [ (unsigned)Parameters::SAFETY ]  = graph->getParam( one, two, Parameters::SAFETY );
	tmpParam [ (unsigned)Parameters::COMFORT ] = graph->getParam( one, two, Parameters::COMFORT );
	
	param[ (unsigned)Parameters::COST ]    += graph->getParam( one, two, Parameters::COST );
	param[ (unsigned)Parameters::TIME ]    += tmpParam[ (unsigned)Parameters::TIME ];
	param[ (unsigned)Parameters::SAFETY ]  += tmpParam[ (unsigned)Parameters::TIME ] * tmpParam[ (unsigned)Parameters::SAFETY ];
	param[ (unsigned)Parameters::COMFORT ] += tmpParam[ (unsigned)Parameters::TIME ] * tmpParam[ (unsigned)Parameters::COMFORT ];	

}

void Path::print() const
{
	std::cout << "Path: [" << rating << "] " << std::endl;

	std::cout << "   ";

	for( unsigned i = 0; i < length; i++)
		std::cout << " "<< path[ i ];

	std::cout << std::endl;
}
