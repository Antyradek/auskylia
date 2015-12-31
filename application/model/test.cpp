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

void graph_test()
{
	DBG("Starting graph test:");

	const unsigned GRAPH_SIZE = 10;

	Graph graph1 = Graph( GRAPH_SIZE, new UniformIntervals() );
	Graph graph2 = Graph( GRAPH_SIZE, new OtherGenerator() );
	Graph graph3 = Graph( GRAPH_SIZE, new SmartGenerator() );

	graph1.print();
	graph2.print();
	graph3.print();

}

int main()
{
	graph_test();
        
	Model model;

        std::cout << "It doesn't do much project-related yet, but it can spawn dragons:" << std::endl << std::endl << dragon << std::endl;


        return 0;
}
