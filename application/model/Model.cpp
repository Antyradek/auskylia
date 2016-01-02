/**
 *  \file   Model.cpp
 *
 *  \authors Andrzej Roguski, Tomasz Jakubczyk
 *
 *  \brief  Definicja klasy Model.
 *
 */

#include "Model.hpp"

/**< \todo przydały by się jakieś wyjątki do modelu */

Graph * Model::generateGraph( unsigned nodes ) const
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

void Model::evolve( unsigned times )
{

}

void setStrategy( const Strategy * strategy )
{
}

void setMutation( const Mutation * mutation )
{
}

Population * Model::getPopulation()
{
	return nullptr;
}

Model::Model() :graph(nullptr),
				population(nullptr),
				strategy(nullptr),
				mutation(nullptr),
				controllerBlockingQueue(nullptr)
{

}


void Model::doMainJob()
{
	if(controllerBlockingQueue==nullptr)
	{
		throw "tu powinien być odpowiedni wyjątek";/**< \todo rzucić odpowiedni wyjątek, jak już powstanie */
	}
	/**< \todo jeszcze nie wiem, czy ta metoda na pewno będzie potrzebna */
}

void Model::setControllerBlockingQueue(BlockingQueue<Event*>* q)
{
	controllerBlockingQueue=q;
}

















