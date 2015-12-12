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

using namespace std;

int main(int argc, char* argv[])
{
	int portNo=8080;
	try
	{
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
		cout<<e.what()<<endl;
	}
	catch(...)/**< \todo napisać lepszą obsługę wyjątków */
	{
		cerr<<"Jakiś wyjątek!"<<endl;
	}
}

















