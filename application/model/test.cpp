
#include <iostream>
#include <string>
#include <cstdlib>>

#include "Model.hpp"

#include "debug.hpp"

const std::string dragon =
"  .     _///_,                      \n"
" .      / ` ' '>                    \n"
"   )   o'  __/_'>                   \n"
"  (   /  _/  )_\\'>                  \n"
"   ' \"__/   /_/\\_>                  \n"
"       ____/_/_/_/                  \n"
"      /,---, _/ /                   \n"
"     ""  /_/_/_/                    \n"
"        /_(_(_(_                 \\  \n"
"       (   \\_\\_\\\\_               )\\ \n"
"        \\'__\\_\\_\\_\\__            ).\\\n"
"        //____|___\\__)           )_/\n"
"        |  _  \\'___'_(           /' \n"
"         \\_ (-'\\'___'_\\      __,'_' \n"
"         __) \\  \\___(_   __/.__,'  \n"
"      ,((,-,__\\  '\", __\\_/. __,'    \n"
"                   '\"./_._._-'      \n"
;


void roll_test()
{
	const unsigned SIZE = 50;
	const unsigned ROLLS_SMALL = 1500;
	const unsigned ROLLS_BIG = 150000;

	unsigned uniform[ SIZE ];
	unsigned binomial[ SIZE ];
	unsigned binomial2[ SIZE ];
	unsigned binomial3[ SIZE ];

	for( unsigned i = 0; i < SIZE; i++ )
	{
		uniform[ i ] = 0;
		binomial[ i ] = 0;
		binomial2[ i ] = 0;
		binomial3[ i ] = 0;
	}

	for( unsigned i = 0; i < ROLLS_SMALL; i++ )
	{
		++uniform[ rollUniform( 0, SIZE-1 ) ];
		++binomial[ rollBinomial( SIZE/2, 0, SIZE-1 ) ];
		++binomial2[ rollBinomialWide( SIZE/2, 0, SIZE-1 ) ];
		++binomial3[ rollBinomialUltraWide( SIZE/2, 0, SIZE-1 ) ];
	}


	for( unsigned i = 0; i < SIZE; i++ )
	{
		std::cout << i << ": ";

		for( unsigned j = 0; j < uniform[ i ]; j++ )
			std::cout << '#';
		
		std::cout << std::endl;
	}

	for( unsigned i = 0; i < SIZE; i++ )
	{
		std::cout << i << ": ";

		for( unsigned j = 0; j < binomial[ i ]; j++ )
			std::cout << '#';
		
		std::cout << std::endl;
	}

	for( unsigned i = 0; i < SIZE; i++ )
	{
		std::cout << i << ": ";

		for( unsigned j = 0; j < binomial2[ i ]; j++ )
			std::cout << '#';
		
		std::cout << std::endl;
	}

	for( unsigned i = 0; i < SIZE; i++ )
	{
		std::cout << i << ": ";

		for( unsigned j = 0; j < binomial3[ i ]; j++ )
			std::cout << '#';
		
		std::cout << std::endl;
	}

	for( unsigned i = 0; i < SIZE; i++ )
	{
		uniform[ i ] = 0;
		binomial[ i ] = 0;
		binomial2[ i ] = 0;
		binomial3[ i ] = 0;
	}

	for( unsigned i = 0; i < ROLLS_BIG; i++ )
	{
		++uniform[ rollUniform( 0, SIZE-1 ) ];
		++binomial[ rollBinomial( SIZE/2, 0, SIZE-1 ) ];
		++binomial2[ rollBinomialWide( SIZE/2, 0, SIZE-1 ) ];
		++binomial3[ rollBinomialUltraWide( SIZE/2, 0, SIZE-1 ) ];
	}


	for( unsigned i = 0; i < SIZE; i++ )
		std::cout << i << ": " << uniform[ i ] << std::endl;

	for( unsigned i = 0; i < SIZE; i++ )
		std::cout << i << ": " << binomial[ i ] << std::endl;

	for( unsigned i = 0; i < SIZE; i++ )
		std::cout << i << ": " << binomial2[ i ] << std::endl;

	for( unsigned i = 0; i < SIZE; i++ )
		std::cout << i << ": " << binomial3[ i ] << std::endl;

}

void graph_test( std::array<unsigned short, (unsigned)Parameters::Count> a )
{
	DBG("Starting graph test:");

	const unsigned GRAPH_SIZE = 10;

	Graph graph1 = Graph( GRAPH_SIZE, new UniformIntervals() );
	Graph graph2 = Graph( GRAPH_SIZE, new OtherGenerator() );
	Graph graph3 = Graph( GRAPH_SIZE, new SmartGenerator() );

	graph1.rate(a);
	graph2.rate(a);
	graph3.rate(a);

	graph1.print();
	graph2.print();
	graph3.print();

	graph1.printRates();
	graph2.printRates();
	graph3.printRates();
}

void pathTest( unsigned start, unsigned end, unsigned maxl, unsigned size)
{
	const unsigned GRAPH_SIZE = size;

	Graph graph1 = Graph( GRAPH_SIZE, new UniformIntervals() );
	
	graph1.rate( std::array<unsigned short, (unsigned)Parameters::Count>{ 20, 20, 20, 20 }  );

	unsigned a [20] = {0,1,2,3,4,5, NULL_NODE ,7,8,9,10,11, NULL_NODE ,13,14,15,16,17,18,19};

	Path p = Path(a, 20, &graph1 );
}

void populationTest( unsigned gSize, unsigned pSize )
{
	Graph graph = Graph( gSize, new UniformIntervals() );
	graph.rate( std::array<unsigned short, (unsigned)Parameters::Count>{ 20, 20, 20, 20 }  );

	StrategyClosest str = StrategyClosest();
	MutationUniform mut;

	Population pop( 3, 7, &graph, &mut, &str, pSize);

	pop.print();

	for(int i = 0; i < 100; ++i)
		pop.evolve( );

	pop.print();
}

int main(int argc, char ** argv)
{

	const unsigned NUM_ARGS = 2;

	if(argc > NUM_ARGS)
	{
		unsigned arg[ NUM_ARGS ];

		for(int i = 1; i<NUM_ARGS + 1; i++)
			arg[i-1] = std::stoi(std::string(argv[i]));

		populationTest( arg[0], arg[1] );
		//pathTest( arg[0], arg[1], arg[2], arg[3]);
	}

	Model model;

        std::cout << "It doesn't do much project-related yet, but it can spawn dragons:" << std::endl << std::endl << dragon << std::endl;


        return 0;
}

