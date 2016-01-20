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
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <sstream>


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

unsigned Model::loadAirportList( const std::string filename )
{
	DBG("Model::loadAirportList()");

	std::ifstream file ( filename );

	std::string str;

	while( ! file.eof() )
	{
		std::getline( file, str );
	}

}

void Model::setEndNodes( unsigned start, unsigned end )
{
	this->start = start;
	this->end   = end;

	if(graph)
		graph->setEndNodes( start, end );
}

unsigned Model::loadIataList( const std::string filename )
{
	DBG("Model::loadIataList( " << filename << " )");

	std::ifstream file ( filename );

	std::string str;

	unsigned count = 0;

	airportList.clear();/**< trzeba wyczycić, jeśli wczytujemy jescze raz */

	while( ! file.eof() )
	{
		std::getline( file, str );
		str=str.substr(0,3);
		airportList.push_back( str );
		++count;
	}

	return count;

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
		for( unsigned i = 0; i < times && !shutDown && !stopCalc; ++i )
		{
			if(stopCalc)
			{
				cout<<endl<<"zatrzymywanie obliczeń"<<endl<<endl;
			}
			evolutionStep=i;
			population->evolve();
		}
	evolutionStep=times;
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

Path Model::getPath ( unsigned n )
{
	DBG("Model::getPath()");

	if( !population )
		throw ("No population");
	
	Path p = *(population->getPath(n));

	unsigned l = p.getLength();

	for(unsigned i = 0; i < l; ++i)
	{
		if( p[i] == start )
			p[i] = 0;
		
		if( p[i] == end )
			p[i] = graph->getNodes();
	}

	return p;

}

std::vector<std::string> Model::getPathIata ( unsigned n )
{
	DBG("Model::getPathIata()");
	if( !population )
		throw ("No population");

	Path p = Path( *(population->getPath(n)) );

	unsigned l = p.getLength();

	std::vector<std::string> v ( l );

	for( unsigned i = 0; i < l; ++i )
	{
		v[i] = airportList[ p[i] ];
		
		if( p[i] == start )
			v[i] = airportList[ 0 ];

		if( p[i] == end )
			v[i] = airportList[ graph->getNodes() - 1 ];

	}

	return v;
}


Model::Model() : graph(nullptr),
		 population(nullptr),
		 controllerBlockingQueue(nullptr),
		 modelBlockingQueue(nullptr),
		 shutDown(false),
		 evolutionStep(0),
		 stopCalc(false)
{
	modelBlockingQueue=new BlockingQueue<Command*>;
}

/*void modelTest( unsigned gSize, unsigned pSize, Model* model)
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
}*/


int v1=50,v2=50,v3=50,v4=50;

void modelTest( unsigned gSize, unsigned pSize, Model* model, unsigned iter )
{
	using namespace std::chrono;

	std::cout << std::endl << "Starting model test:" << std::endl;

	Model* m=model;
	StrategyClosest s;
	MutationUniform mut;
	GeneratorUniform gen;

	Weights w1 = { v1, v2, v3, v4};
	Weights w2 = { 1, 1, 100, 1};

	auto gen_start = steady_clock::now();

	Graph * g = m->generateGraph( gSize, &gen );

	auto gen_stop = steady_clock::now();

	m->useGraph(g);

	auto pop_start = steady_clock::now();

	m->createPopulation( pSize, &s, &mut );

	auto pop_stop = steady_clock::now();

	std::cout << std::endl << "Wagi "<<v1<<", "<<v2<<", "<<v3<<", "<<v4<< std::endl;

	m->setWeights( w1 );

	m->getPopulation()->print();

	auto ev_start = steady_clock::now();

	m->evolve( iter );

	auto ev_stop = steady_clock::now();

	m->getPopulation()->print();

	std::cout << std::endl;
	std::cout << "Wierzchołki:                      " << gSize                                                      <<std::endl;
	std::cout << "Populacja:                        " << pSize                                                      <<std::endl;
	std::cout << "Iteracje:                         " << iter                                                       <<std::endl;
	std::cout << "Czas generowania grafu [ms]:      " << duration<double, std::milli>(gen_stop - gen_start).count() <<std::endl;
	std::cout << "Czas generowania populacji [ms]:  " << duration<double, std::milli>(pop_stop - pop_start).count() <<std::endl;
	std::cout << "Czas ewolucji [ms]:               " << duration<double, std::milli>(ev_stop  - ev_start ).count() <<std::endl;
	std::cout << std::endl;
}

string Model::getIATAbyId(int id)
{
	if(airportList.empty())
	{
		loadIataList("iata_list");
	}
	if(airportList.empty())
	{
		cout<<"Lista IATA jest pusta"<<endl;
		return string("WAW");
	}
	else
	{
		return airportList.at(id);/**< tu może walnąć wyjątkiem, jeśli id będzie większe niż lista */
	}
}

ostringstream ss;

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
			stopCalc=false;
			status=0;
			modelStatus=new ModelStatus;
			modelStatus->status=status;
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL,modelStatus));

			unsigned gSize=3464;
			unsigned pSize=100;
			unsigned iter=100;//000;
			v1=strtol(c->price.c_str(),0,10);
			v2=strtol(c->safety.c_str(),0,10);
			v3=strtol(c->comfort.c_str(),0,10);
			v4=strtol(c->price.c_str(),0,10);
			thread modelTestThread(modelTest,gSize,pSize,this,iter);
			//modelTest(10,10,this,1000);
			while(evolutionStep+1<iter && !stopCalc)
			{
				this_thread::sleep_for (chrono::seconds(1));
				status=(int)(100.0f*(double)evolutionStep/(double)iter);
				#ifdef _DEBUG
				coutMutex.lock();
				cout<<"status: "<<status<<endl;
				cout<<"evolutionStep: "<<evolutionStep<<endl;
				coutMutex.unlock();
				#endif // DEBUG
				modelStatus=new ModelStatus;
				modelStatus->status=status;
				controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL,modelStatus));
			}
			cout<<endl<<"waiting for modelTestThread join..."<<endl;
			modelTestThread.join();
			cout<<endl<<"modelTestThread joined"<<endl<<endl;
			status=100;
			//można opcjonalnie zwrócić, że działa
			modelStatus=new ModelStatus;
			modelStatus->status=status;
			modelStatus->result=true;
			string pom="";
			Path p = getPath( 0 );
			unsigned l = p.getLength();
			for( unsigned i = 0; i < l; ++i)
			{
				pom+="<airport><iata>"+getIATAbyId(p[i])+"</iata></airport>";
			}
			modelStatus->str="<data><response>success</response><airports><airport><iata>"+c->start+"</iata></airport>"+pom+"<airport><iata>"+c->end+"</iata></airport></airports></data>\0";
			/**< \todo zwrócić wynik algorytmu */
			controllerBlockingQueue->push_back(new Event(MESSAGE_FROM_MODEL,modelStatus));
		}
		else if(c->commandType==CommandType::STOP)
		{
			/**< \todo zatrzymać algorytm */
			stopCalc=true;
			cout<<"polecenie zatrzymania obliczeń"<<endl;
			if(stopCalc)
			{
				cout<<"stopCalc ustawione"<<endl;
			}
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


























