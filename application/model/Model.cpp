/** 
 *  \file   Model.cpp
 *
 *  \author Andrzej Roguski
 *  
 *  \brief  Definicja klasy Model.
 *
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

void Model::setTargetPath( const std::array<unsigned short, (unsigned)Parameters::Count> & weights, unsigned start, unsigned end )
{

}

void Model::createPopulation( unsigned size )
{

}

void Model::evolve( unsigned times, const Strategy & strategy )
{

}

void setStrategy( Strategy strategy )
{
	this->strategy = strategy;
}

void setMutation( Mutation mutation )
{
	this->mutation = mutation;
}

Population * Model::getPopulation()
{
	return nullptr;
}
