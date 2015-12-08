/** \file Controller.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Controller
 *
 */

#include <thread>

Controller::Controller() : shutDown(false)
{

}

Controller::~Controller()
{

}

void Controller::setModel(Model* m)
{
	model=m;
}

void Controller::setViewServer(ViewServer* v)
{
	viewServer=v;
}

void Controller::start()
{
	/**< \todo nadrzędna pętla do wielokrotnego uruchamiania obliczeń */
	while(!shutDown)
	{
		std::thread viewServerThread(viewServer->listenAndRespond());
		/**< \todo odebrać polecenie rozpoczęcia obliczeń z ich parametrami */
		std::thread modelMainThread(model->doMainJob(auto parametry));/**< \todo potrzebna znajomość
		interfejsu publicznego modelu */
		/**< \todo pętla do przetwarzania zapytań, komunikatów i zdarzeń */
		while(!shutDown)
		{
			/**< \todo dopuki model liczy odpowiadać */
		}
	}
}

























