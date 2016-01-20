/** \file controllerMain.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik główny z mainem kontrolera aplikacji auskylia.
 *
 */

#include "Controller.hpp"
#include "version.h"
#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>
#include <thread>

#include <mutex>
std::mutex coutMutex;/**< mutex do zapewniania niepodzielności cout między wątkami */

using namespace std;

int main(int argc, char* argv[])
{
	int portNo=5005;
	try
	{
		coutMutex.lock();
		cout<<"Serwer Auskylia wystartował..."<<endl;
		cout<<"Build Version:"<<endl<<AutoVersion::FULLVERSION_STRING<<endl;
		cout<<"Build Date: "<<endl<<AutoVersion::DATE<<"."<<AutoVersion::MONTH<<"."<<AutoVersion::YEAR<<endl;
		coutMutex.unlock();
		if(argc>=2)
		{
			portNo=strtol(argv[1],0,10);
		}
		cout<<"Aplikacja dostępna na porcie: "<<portNo<<endl;
		Controller* controller=new Controller();
		controller->setModel(new Model());
		controller->setViewServer(new ViewServer(portNo));
		controller->setup();
		//controller->start();
		thread controllerThread(&Controller::start,controller);
		string s;
		while(cin>>s)//bżydkie ale wygodne
		{
			if(s.compare("exit")==0)
			{
				controller->triggerShutDown();
				break;
			}
		}
		controllerThread.join();
	}
	catch(exception &e)
	{
		coutMutex.lock();
		cout<<e.what()<<endl;
		coutMutex.unlock();
	}
	catch(...)/**< \todo napisać lepszą obsługę wyjątków */
	{
		coutMutex.lock();
		cerr<<"Jakiś wyjątek!"<<endl;
		coutMutex.unlock();
	}
}

















