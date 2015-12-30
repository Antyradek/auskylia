#include <iostream>
#include <string>

#include "Model.hpp"


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

const unsigned SIZE = 50;
const unsigned ROLLS_SMALL = 1500;

const unsigned ROLLS_BIG = 150000;
int main()
{
	unsigned uniform[ SIZE ];
	unsigned binomial[ SIZE ];
	unsigned binomial2[ SIZE ];

	for( int i = 0; i < SIZE; i++ )
	{
		uniform[ i ] = 0;
		binomial[ i ] = 0;
		binomial2[ i ] = 0;
	}

	for( int i = 0; i < ROLLS_SMALL; i++ )
	{
		++uniform[ rollUniform( 0, SIZE-1 ) ];
		++binomial[ rollBinomial( SIZE/2, 0, SIZE-1 ) ];
		++binomial2[ rollBinomial( SIZE/8, 0, SIZE-1 ) ];
	}


	for( int i = 0; i < SIZE; i++ )
	{
		std::cout << i << ": ";

		for( int j = 0; j < uniform[ i ]; j++ )
			std::cout << '#';
		
		std::cout << std::endl;
	}

	for( int i = 0; i < SIZE; i++ )
	{
		std::cout << i << ": ";

		for( int j = 0; j < binomial[ i ]; j++ )
			std::cout << '#';
		
		std::cout << std::endl;
	}

	for( int i = 0; i < SIZE; i++ )
	{
		std::cout << i << ": ";

		for( int j = 0; j < binomial2[ i ]; j++ )
			std::cout << '#';
		
		std::cout << std::endl;
	}

	for( int i = 0; i < SIZE; i++ )
	{
		uniform[ i ] = 0;
		binomial[ i ] = 0;
		binomial2[ i ] = 0;
	}

	for( int i = 0; i < ROLLS_BIG; i++ )
	{
		++uniform[ rollUniform( 0, SIZE-1 ) ];
		++binomial[ rollBinomial( SIZE/2, 0, SIZE-1 ) ];
		++binomial2[ rollBinomial( SIZE/8, 0, SIZE-1 ) ];
	}


	for( int i = 0; i < SIZE; i++ )
		std::cout << i << ": " << uniform[ i ] << std::endl;

	for( int i = 0; i < SIZE; i++ )
		std::cout << i << ": " << binomial[ i ] << std::endl;

	for( int i = 0; i < SIZE; i++ )
		std::cout << i << ": " << binomial2[ i ] << std::endl;
        Model model;

        std::cout << "It doesn't do much project-related yet, but it can spawn dragons:" << std::endl << std::endl << dragon << std::endl;


        return 0;
}
