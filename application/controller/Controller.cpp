/** \file Controller.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Controller
 *
 */

#include "Controller.hpp"
#include <thread>
#include <exception>
#include <string>

#include <mutex>
extern std::mutex coutMutex;


/** \brief Klasa opakowująca exception dla Controller
 */
struct ControllerException : std::exception
{
private:
	std::string m;
public:
    /** \brief Wygodny kostruktor wyjątku
     * \param std::string s komunikat do wyświetlenia
     */
	ControllerException(std::string s)
	{
		m="ControllerException: "+s+"\n";
	}
    /** \brief przeciążona metoda wyświetla nasz komunikat
     * \return const char* komunikat
     */
	const char* what() const noexcept
	{
		return m.c_str();
	}
};

Controller::Controller() :
	model(nullptr),
	viewServer(nullptr),
	shutDown(false),
	controllerBlockingQueue(nullptr)
{

}

Controller::~Controller()
{
	if(controllerBlockingQueue!=nullptr)
	{
		delete controllerBlockingQueue;
	}
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
	using namespace std;
	/**< \todo nadrzędna pętla do wielokrotnego uruchamiania obliczeń */
	while(!shutDown)
	{
		std::thread viewServerThread(&ViewServer::listenAndRespond, viewServer);
		/**< \todo odebrać polecenie rozpoczęcia obliczeń z ich parametrami */
		std::thread modelMainThread(&Model::doMainJob, model);/**< \todo potrzebna znajomość
		interfejsu publicznego modelu */
		/**< \todo pętla do przetwarzania zapytań, komunikatów i zdarzeń */
		while(!shutDown)
		{
			/**< \todo dopóki model liczy odpowiadać */
			Event* e=nullptr;
			e=controllerBlockingQueue->pop_front();//pobieramy zdarzenie
			/** \todo jeśli komuś się będzie bardzo nudziło,
			 * to może przerobić tego switcha na mapę strategii */
            switch (e->type)
            {
			case Test:
				break;
			case MESSAGE_FROM_VIEW_SERVER:
				break;
			case MESSAGE_FROM_MODEL:
				break;
			default:
				coutMutex.lock();
				clog<<"nieznane zdarzenie"<<endl;
				coutMutex.unlock();
            }
            delete e;
		}
	}
}

void Controller::setup()
{
	if(controllerBlockingQueue!=nullptr)
	{
		throw ControllerException("controllerBlockingQueue!=nullptr");
	}
	controllerBlockingQueue=new BlockingQueue<Event*>;
	if(viewServer==nullptr)
	{
		throw ControllerException("viewServer==nullptr");
	}
	viewServer->setControllerBlockingQueue(controllerBlockingQueue);
}


















































