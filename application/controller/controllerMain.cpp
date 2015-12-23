/** \file controllerMain.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik główny z mainem kontrolera aplikacji auskylia.
 *
 */

#include "Controller.hpp"
#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>

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
		coutMutex.unlock();
		if(argc>=2)
		{
			portNo=strtol(argv[1],0,10);
		}
		Controller* controller=new Controller();
		controller->setModel(new Model());
		controller->setViewServer(new ViewServer(portNo));
		controller->setup();
		controller->start();
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

















