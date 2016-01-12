#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

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
	std::cout << std::endl << "Starting graph test:" << std::endl;

	const unsigned GRAPH_SIZE = 10;

	Graph graph1 = Graph( GRAPH_SIZE, new GeneratorUniform() );

	graph1.printNodes();
	graph1.print();
}

void pathTest( unsigned size)
{
	std::cout << std::endl << "Starting path test:" << std::endl;

	const unsigned GRAPH_SIZE = size;

	Graph graph1 = Graph( GRAPH_SIZE, new GeneratorUniform() );
	
	Weights w = { 50, 50, 50, 50};

	Path p = Path( &graph1, w );

	p.print();

}

void populationTest( unsigned gSize, unsigned pSize )
{
	std::cout << std::endl << "Starting population test:" << std::endl;

	GeneratorUniform gen;

	Graph graph = Graph( gSize, &gen );

	StrategyClosest str = StrategyClosest();
	MutationUniform mut;

	Population pop( &graph, &mut, &str, pSize);
	Weights w = { 50, 50, 50, 50};
	pop.setWeights( w );

	pop.print();

	for(int i = 0; i < 100; ++i)
		pop.evolve( );

	pop.print();
}

void modelTest( unsigned gSize, unsigned pSize, unsigned iter )
{
	using namespace std::chrono;

	std::cout << std::endl << "Starting model test:" << std::endl;

	Model m;
	StrategyClosest s;
	MutationUniform mut;
	GeneratorUniform gen;

	Weights w1 = { 50, 50, 50, 50};
	Weights w2 = { 1, 1, 100, 1};

	auto gen_start = steady_clock::now();

	Graph * g = m.generateGraph( gSize, &gen );

	auto gen_stop = steady_clock::now();
	
	m.useGraph(g);

	auto pop_start = steady_clock::now();

	m.createPopulation( pSize, &s, &mut );

	auto pop_stop = steady_clock::now();

	std::cout << std::endl << "Wagi 1.0, 1.0, 1.0, 1.0, 1.0" << std::endl;
	
	m.setWeights( w1 );

	m.getPopulation()->print();

	auto ev_start = steady_clock::now();

	m.evolve( iter );

	auto ev_stop = steady_clock::now();

	m.getPopulation()->print();

	std::cout << std::endl;
	std::cout << "Wierzchołki:                      " << gSize                                                      <<std::endl;
	std::cout << "Populacja:                        " << pSize                                                      <<std::endl;
	std::cout << "Iteracje:                         " << iter                                                       <<std::endl;
	std::cout << "Czas generowania grafu [ms]:      " << duration<double, std::milli>(gen_stop - gen_start).count() <<std::endl;
	std::cout << "Czas generowania populacji [ms]:  " << duration<double, std::milli>(pop_stop - pop_start).count() <<std::endl;
	std::cout << "Czas ewolucji [ms]:               " << duration<double, std::milli>(ev_stop  - ev_start ).count() <<std::endl;
	std::cout << std::endl;
}

int main(int argc, char ** argv)
{

	const unsigned NUM_ARGS = 3;

	if(argc > NUM_ARGS)
	{
		unsigned arg[ NUM_ARGS ];

		for(unsigned i = 1; i<NUM_ARGS + 1; i++)
			arg[i-1] = std::stoi(std::string(argv[i]));

		std::cout << arg[0] << std::endl;
		std::cout << arg[1] << std::endl;
		std::cout << arg[2] << std::endl;


		// graphTest();

		// pathTest( arg[0] );

		//populationTest( arg[0], arg[1] );

		modelTest( arg[0], arg[1], arg[2] );
	}
	else
	{
		std::cout << "Za mało argumentów; podaj liczbę wierzcholków, rozmiar populacji i liczbę ewolucji." << std::endl;
	}

        std::cout << "It does quite a lot project-related now and it still can spawn dragons!" << std::endl << std::endl << dragon << std::endl;


        return 0;
}
