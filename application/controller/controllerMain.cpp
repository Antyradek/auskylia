/** \file controllerMain.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik główny z mainem kontrolera aplikacji auskylia.
 *
 */

#include "Controller.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	int portNo=8080;
	try
	{
		if(argc>=2)
		{
			portNo=stoi(string(argv[1]));
		}
		Controller* controller=new Controller();
		controller->setModel(new Model());
		controller->setViewServer(new ViewServer(portNo));
		controller->start();
	}
	catch(..)/**< \todo napisać lepszą obsługę wyjątków */
	{
		cerr<<"Jakiś wyjątek!"<<endl;
	}
}

















