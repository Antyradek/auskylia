#include <iostream>
#include <string>

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

void graphTest( )
{
	DBG_DO(std::cout << std::endl);
	DBG("Starting graph test:");

	const unsigned GRAPH_SIZE = 10;

	Graph graph1 = Graph( GRAPH_SIZE, new GeneratorUniform() );

	graph1.printNodes();
	graph1.print();
}

void pathTest( unsigned size)
{
	DBG_DO(std::cout << std::endl);
	DBG("Starting path test:");

	const unsigned GRAPH_SIZE = size;

	Graph graph1 = Graph( GRAPH_SIZE, new GeneratorUniform() );
	
	Weights w = { 100, 100, 100, 100};

	Path p = Path( &graph1, w );

}

void populationTest( unsigned gSize, unsigned pSize )
{
	DBG_DO(std::cout << std::endl);
	DBG("Starting population test:");

	Graph graph = Graph( gSize, new GeneratorUniform() );

	StrategyClosest str = StrategyClosest();
	MutationUniform mut;

	Population pop( 3, 7, &graph, &mut, &str, pSize);
	Weights w = { 100, 100, 100, 100};
	pop.setWeights( w );

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

		graphTest();

		pathTest( arg[0] );

		populationTest( arg[0], arg[1] );
	}

	Model model;

        std::cout << "It doesn't do much project-related yet, but it can spawn dragons:" << std::endl << std::endl << dragon << std::endl;


        return 0;
}
