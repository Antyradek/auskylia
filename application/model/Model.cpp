/** 
 *  \file Model.hpp
 *  \authors Tomasz Jakubczyk, Andrzej Roguski
 *  \brief Plik nagłówkowy klasy Model.
 *
 * \todo Andrzej napisze Model :D
 */

#include "Model.hpp"

Graph * Model::generateGraph( unsigned nodes, bool dense ) const
{
        return nullptr;
}

void Model::useGraph( Graph * const graph )
{

}

void Model::useGraph( const std::string & file )
{

}

void Model::saveGraph( const std::string & file, Graph * graph ) const
{

}

Path * Model::findBestPath( const std::array<unsigned short, (unsigned)Parameters::Count> & weights, unsigned start, unsigned end )
{
        return nullptr;
}
