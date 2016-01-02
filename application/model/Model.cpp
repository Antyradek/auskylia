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
				controllerBlockingQueue(nullptr),
				modelBlockingQueue(nullptr),
				shutDown(false)
{
	modelBlockingQueue=new BlockingQueue<Command*>;
}


void Model::doMainJob()
{
	if(controllerBlockingQueue==nullptr)
	{
		throw "tu powinien być odpowiedni wyjątek";/**< \todo rzucić odpowiedni wyjątek, jak już powstanie */
	}
	if(modelBlockingQueue==nullptr)
	{
		throw "tu powinien być odpowiedni wyjątek";
	}
	Command* c=nullptr;
	while(!shutDown)
	{
		c=modelBlockingQueue->pop_front();
		if(c->commandType==CommandType::START)
		{
			/**< \todo wziąć dane z polecenia i uruchomić algorytm */
			//można opcjonalnie zwrócić, że działa
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL));
		}
		else if(c->commandType==CommandType::STOP)
		{
			/**< \todo zatrzymać algorytm */
			//też opcjonalne zgłoszenie, że zatrzymaliśmy
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL));
		}
		else if(c->commandType==CommandType::STATUS)
		{
			/**< \todo zwrócić stan wykonania algorytmu */
			//ważne zgłoszenie o stanie wykonania
			/**< \todo wymyślić wygodny sposób zwracania stanu */
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL));
		}
		delete c;
	}
}

void Model::setControllerBlockingQueue(BlockingQueue<Event*>* q)
{
	controllerBlockingQueue=q;
}

















