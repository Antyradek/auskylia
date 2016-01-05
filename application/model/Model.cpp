/**
 *  \file   Model.cpp
 *
 *  \authors Andrzej Roguski, Tomasz Jakubczyk
 *
 *  \brief  Definicja klasy Model.
 *
 */

#include "Model.hpp"

#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>

extern std::mutex coutMutex;

using namespace std;

/**< \todo przydały by się jakieś wyjątki do modelu */

Graph * Model::generateGraph( unsigned nodes, const GraphGenerator * const generator ) const
{
	return new Graph( nodes, generator );
}

void Model::useGraph( Graph * const graph )
{
	this->graph = graph;
}

void Model::useGraph( const std::string & file )
{

}

void Model::saveGraph( const std::string & file, Graph * graph ) const
{

}

void Model::setWeights( const Weights & weights )
{
	DBG(" Model::setWeights() ");
	DBG(" " << weights[0] << " " << weights[1] << " " << weights[2] << " " << weights[3]  );
	if( population != nullptr )
		population->setWeights(weights);
}

void Model::createPopulation( unsigned size, Strategy * strategy, Mutation * mutation )
{
	if( graph != nullptr )
		population = new Population( graph, mutation, strategy, size );
}

void Model::evolve( unsigned times )
{
	if( population != nullptr )
		for( unsigned i = 0; i < times; ++i )
			population->evolve();
}

void Model::setStrategy( Strategy * strategy )
{
	if( population != nullptr )
		population->setStrategy( strategy );
}

void Model::setMutation( Mutation * mutation )
{
	if( population != nullptr )
		population->setMutation( mutation );
}

Population * Model::getPopulation()
{
	return population;
}

Model::Model() : graph(nullptr),
		 population(nullptr),
		 controllerBlockingQueue(nullptr),
		 modelBlockingQueue(nullptr),
		 shutDown(false)
{
	modelBlockingQueue=new BlockingQueue<Command*>;
}

void modelTest( unsigned gSize, unsigned pSize, Model* model)
{
	std::cout << std::endl << "Starting model test:" << std::endl;

	Model* m=model;
	StrategyClosest s;
	MutationUniform mut;
	GeneratorUniform gen;
	Weights w = { 100, 100, 100, 100};

	Graph * g = m->generateGraph( gSize, &gen );

	m->useGraph(g);

	m->createPopulation( pSize, &s, &mut );

	m->setWeights( w );

	m->getPopulation()->print();

	m->evolve(1000);

	m->getPopulation()->print();
}

void Model::doMainJob()
{
	int status=0;
	ModelStatus* modelStatus=nullptr;
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
			status=0;
			modelStatus=new ModelStatus;
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL,modelStatus));
			modelTest(10,10,this);
			for(int i=10;i<100;i+=10)
			{
				this_thread::sleep_for (chrono::seconds(1));
				status=i;
				modelStatus=new ModelStatus;
				modelStatus->status=status;
				controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL,modelStatus));
			}
			status=100;
			//można opcjonalnie zwrócić, że działa
			modelStatus=new ModelStatus;
			modelStatus->status=status;
			modelStatus->result=true;
			/**< \todo zwrócić wynik algorytmu */
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL,modelStatus));
		}
		else if(c->commandType==CommandType::STOP)
		{
			/**< \todo zatrzymać algorytm */
			//też opcjonalne zgłoszenie, że zatrzymaliśmy
			modelStatus=new ModelStatus;
			modelStatus->status=status;
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL,modelStatus));
		}
		else if(c->commandType==CommandType::STATUS)
		{
			/**< \todo zwrócić stan wykonania algorytmu */
			//ważne zgłoszenie o stanie wykonania
			modelStatus=new ModelStatus;
			modelStatus->status=status;
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL,modelStatus));
		}
		delete c;
	}
}

void Model::setControllerBlockingQueue(BlockingQueue<Event*>* q)
{
	controllerBlockingQueue=q;
}

void Model::triggerShutDown()
{
	#ifdef _DEBUG
	coutMutex.lock();
	cout<<"Model::triggerShutDown()"<<endl;
	coutMutex.unlock();
	#endif // _DEBUG
	shutDown=true;
	modelBlockingQueue->push_back(new Command(CommandType::STOP));/**< primo odblokowuje kolejkę, sekundo daje szansę na porawne zakończenie algorytmu */
}


























