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

void Model::setTargetPath( const std::array<unsigned short, (unsigned)Parameters::Count> & weights, unsigned start, unsigned end ){}

void Model::createPopulation( unsigned size ){}

void Model::evolve( unsigned times, Strategy strategy ){}

Population * Model::getPopulation()
{
        return nullptr;
}