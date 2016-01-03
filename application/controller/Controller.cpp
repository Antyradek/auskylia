/** \file Controller.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Controller
 *
 */

#include "Controller.hpp"
#include "Message.hpp"
#include "Command.hpp"
#include <thread>
#include <exception>
#include <string>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <fstream>
#include <limits>

extern std::mutex coutMutex;

using namespace std;

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
	shutDown=false;
	mutex m;
	unique_lock<mutex> timerLock(m);
	condition_variable c;
	Message * msg=nullptr;
	string str;
	fstream f;
	int len;
	char* buf=nullptr;
	int status;
	ostringstream ss;
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
			case SHUT_DOWN:
				coutMutex.lock();
				cout<<"Zamykanie serwera Auskylia..."<<endl;
				coutMutex.unlock();
				viewServer->triggerShutDown();
				//viewServerThread.join();
				modelMainThread.join();/**< \todo model powinien przyjmować polecenie zamknięcia */
				cout<<"Oczekuję na zamknięcie ViewServer: ";
				cout.flush();
				for(int i=10;i>=0;i--)
				{
					cout<<i<<", ";
					cout.flush();
					c.wait_for(timerLock,chrono::seconds(1));
				}
				break;
			case MESSAGE_FROM_VIEW_SERVER:
				msg=(Message*)e->data;
				coutMutex.lock();
				cout<<"Wiadomość z widoku: "<<msg->msg<<endl;
				cout<<"msg->messageType: "<<msg->messageType<<endl;
				coutMutex.unlock();
				if(msg->messageType==MessageType::LIST)
				{
					#ifdef _DEBUG
					coutMutex.lock();
					cout<<"msg->messageType==LIST"<<endl;
					coutMutex.unlock();
					#endif // _DEBUG
					f.open("airports.xml",fstream::in | fstream::binary);
					if(!f.is_open())
					{
						f.open("../../airports.xml",fstream::in | fstream::binary);
					}
					if(!f.is_open())
					{
						cout<<"nie znaleziono pliku airports.xml"<<endl;
					}
					f.seekg(0,f.end);
					len=f.tellg();
					#ifdef _DEBUG
					coutMutex.lock();
					cout<<"len: "<<len<<endl;
					coutMutex.unlock();
					#endif // _DEBUG
					buf=new char[len+1];
					f.seekg(0,f.beg);
					f.readsome(buf,len);
					f.close();
					str=string(buf);
					delete[] buf;
					buf=nullptr;
					viewServer->viewServerBlockingQueue->push_back(str);
					#ifdef _DEBUG
					coutMutex.lock();
					cout<<"lista lotnisk: "<<endl;
					cout<<str<<endl;
					cout<<"lista lotnisk wrzucona na kolejkę"<<endl;
					coutMutex.unlock();
					#endif // _DEBUG
				}
				else if(msg->messageType==MessageType::CALCULATE)
				{
					str="<data><response>progress</response><progress>0</progress></data>";
					viewServer->viewServerBlockingQueue->push_back(str);
					/**< \todo uruchomić zadanie w modelu */
					model->modelBlockingQueue->push_back(new Command(CommandType::START));
				}
				else if(msg->messageType==MessageType::STATUS)
				{
					status=0;
					/**< \todo sprawdzić postępy w modelu */
					#ifdef __CYGWIN__
					ss << status;
					str = ss.str();
					#else
					str="<data><response>progress</response><progress>"+to_string(status)+"</progress></data>";
					#endif // __CYGWIN__
					/**< \todo możliwe są jeszcze odpowiedzi o zakończeniu lub porażce */
					viewServer->viewServerBlockingQueue->push_back(str);
				}
				else if(msg->messageType==MessageType::STOP)
				{
					str="<data><response>failture</response><cause>Przerwano obliczenia.</cause></data>";
					viewServer->viewServerBlockingQueue->push_back(str);
					/**< \todo w modelu przerwać obliczenia */
				}
				break;
			case MESSAGE_FROM_MODEL:
				coutMutex.lock();
				cout<<"Wiadomość z modelu: "<<endl;
				coutMutex.unlock();
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
	model->setControllerBlockingQueue(controllerBlockingQueue);
}

void Controller::triggerShutDown()
{
	shutDown=true;
	if(controllerBlockingQueue==nullptr)
	{
		throw ControllerException("Controller::triggerShutDown() controllerBlockingQueue==nullptr");
	}
	controllerBlockingQueue->push_back(new Event(SHUT_DOWN));
}


















































