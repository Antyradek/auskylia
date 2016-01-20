/** \file ViweServer.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy ViewServer
 *
 */

#include "ViewServer.hpp"
#include "XMLParser.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <exception>

#include <mutex>
extern std::mutex coutMutex;

using namespace std;

/** \brief Klasa opakowująca exception dla ViewServer
 */
struct ViewServerException : std::exception
{
private:
	std::string m;
public:
    /** \brief Wygodny kostruktor wyjątku
     * \param std::string s komunikat do wyświetlenia
     */
	ViewServerException(std::string s)
	{
		m="ViewServerException: "+s+"\n";
	}
    /** \brief przeciążona metoda wyświetla nasz komunikat
     * \return const char* komunikat
     */
	const char* what() const noexcept
	{
		return m.c_str();
	}
};

ViewServer::ViewServer(int pNo) :
	viewServerBlockingQueue(nullptr),
	portNo(pNo),
	controllerBlockingQueue(nullptr),
	shutDown(false),
	closed(false)
{
	viewServerBlockingQueue=new BlockingQueue<std::string>;
}

ViewServer::~ViewServer()
{
	if(viewServerBlockingQueue!=nullptr)
	{
		delete viewServerBlockingQueue;
	}
}


/** \brief Metoda odpowiedzialna za komunikację sieciową z widokiem.
 * Możliwe podobieństwa do https://en.wikipedia.org/wiki/Berkeley_sockets
 *
 * \return void
 *
 */
void ViewServer::listenAndRespond()
{
	using namespace std;/**< \todo ujednolicić std namespace */

	if(controllerBlockingQueue==nullptr)
	{
		throw ViewServerException("controllerBlockingQueue==nullptr");
	}

	shutDown=false;
	closed=false;

	struct sockaddr_in sa;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (-1 == SocketFD)
	{
      perror("Nie udało się utworzyć gniazda");
      exit(EXIT_FAILURE);
    }
    #ifdef _DEBUG
    coutMutex.lock();
    std::cout<<"Gniazdo utworzone\n";
    coutMutex.unlock();
    #endif // _DEBUG

    memset(&sa, 0, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(portNo);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int reuseaddr = 1;
	setsockopt(SocketFD, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
    
    if (-1 == bind(SocketFD,(struct sockaddr *)&sa, sizeof sa))
	{
      perror("Połączenie nieudane");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    #ifdef _DEBUG
    coutMutex.lock();
    std::cout<<"Połączenie sukcesywne\n";//bind to nie to samo co połączenie
    coutMutex.unlock();
    #endif // _DEBUG

    if (-1 == listen(SocketFD, 10))
	{
      perror("Nasłuchiwanie nieudane");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    #ifdef _DEBUG
    coutMutex.lock();
    std::cout<<"Nasłuchiwanie...\n";
    coutMutex.unlock();
    #endif // _DEBUG

    XMLParser xmlParser;

    while(!shutDown)/**< \todo ustalić czas życia gniazda w naszej aplikacji */
	{
		int ConnectFD = accept(SocketFD, NULL, NULL);

		if (0 > ConnectFD)
		{
			perror("Akceptacja nieudana");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}
		#ifdef _DEBUG
		coutMutex.lock();
		std::cout<<"Połączenie zaakceptowane\n";
		coutMutex.unlock();
		#endif // _DEBUG

		/**< \todo zczytać zapytanie od widoku */
		/**< \todo odesłać odpowiedź z nagłówkiem HTTP */
		/* perform read write operations ...
		read(ConnectFD, buff, size)
		*/
		int siz=1024;
		char* buf=new char[siz];
		read(ConnectFD, buf, siz);
		#ifdef _DEBUG2
		coutMutex.lock();
		std::cout<< "Odebrano dane:" << std::endl << buf << std::endl;
		coutMutex.unlock();
		#endif // _DEBUG

		string msg(buf);
		#ifdef _DEBUG
		coutMutex.lock();
		cout<<"Dane mają rozmiar: "<<msg.size()<<endl;
		coutMutex.unlock();
		#endif // _DEBUG

		string reqDoc = getPageRequest(msg);
		#ifdef _DEBUG2
		coutMutex.lock();
		cout << "Zapytano się o stronę: " << reqDoc << endl;
		coutMutex.unlock();
		#endif // _DEBUG2

		string body = "";
		string mime = "";
		if(reqDoc == "/server")
		{
			//to zapytanie do serwera, parsujemy XML i generujemy odpowiedź

			//TODO Testowo
			body = "<data><response>failture</response><cause>Ta funkcja jeszcze nie jest gotowa.</cause></data>";

			mime = "text";

			//jakieś dziwne rzeczy się działy z poniższym if'em
			if(true/*msg.size()==0*/ && !shutDown)//z jakiegoś powodu zdażają się puste połączenia
			{
				Message* message=nullptr;
				message=xmlParser(msg);
				Event* e=new Event(MESSAGE_FROM_VIEW_SERVER,(void*)message);
				controllerBlockingQueue->push_back(e);
				body=viewServerBlockingQueue->pop_front();
				#ifdef _DEBUG
				coutMutex.lock();
				cout<<"odebrano dane z kolejki"<<endl;
				coutMutex.unlock();
				#endif // _DEBUG
			}
		}
		else
		{
			//zapytanie o zasoby, musimy zwrócić stronę internetową
			body = getPage(reqDoc, mime);
		}

		string response = "HTTP/1.1 200 OK\nContent-Type: " + mime + "\n\n" + body;
		#ifdef _DEBUG2
		coutMutex.lock();
		cout << "Zwracamy stronę: " << endl << response << endl;
		coutMutex.unlock();
		#endif // _DEBUG2
		const char* data = response.c_str();
		int len = response.size();
		if(!shutDown)
		{
			write(ConnectFD,data,len);
		}

		if (-1 == shutdown(ConnectFD, SHUT_RDWR))
		{
			perror("Nie udało się zakończyć");
			close(ConnectFD);
			close(SocketFD);
			exit(EXIT_FAILURE);
		}
		close(ConnectFD);
		#ifdef _DEBUG
		coutMutex.lock();
		std::cout<<"Połączenie zakończone\n";
		coutMutex.unlock();
		#endif // _DEBUG

	}

    close(SocketFD);
    #ifdef _DEBUG
	coutMutex.lock();
	std::cout<<"Gniazdo zamknięte\n";
	coutMutex.unlock();
	#endif // _DEBUG
	closedMutex.lock();
	closed=true;
	closedMutex.unlock();
}

void ViewServer::setControllerBlockingQueue(BlockingQueue<Event*>* q)
{
	controllerBlockingQueue=q;
}

void ViewServer::triggerShutDown()
{
	shutDown=true;
	viewServerBlockingQueue->push_back(string("shutdown"));
	/**< \todo rozwiązać problem z blokującym accept przy zamykaniu */
	#ifdef _DEBUG
	coutMutex.lock();
	std::cout<<"ViewServer::triggerShutDown()\n";
	coutMutex.unlock();
	#endif // _DEBUG
}

std::string ViewServer::getPageRequest(const std::string& message)
{
	//pierwszy wiersz ma 3 wyrazy, a środkowy jest zasobem.
	int firstSpace = message.find(' ');
	int secondSpace = message.find(' ', firstSpace + 1);
	std::string request = message.substr(firstSpace + 1, secondSpace - firstSpace - 1);
	return request;
}

std::string ViewServer::getPage(std::string resource, std::string& type)
{
	using namespace std;
	std::string viewDir = "view";

	if(resource == "/")
	{
		resource = "/index.html";
	}

	typedef pair<string, string> PagePair;
	//hiperbezpieczna i hiperniewygodna metoda
	std::vector<PagePair> whitelist;
	whitelist.push_back(PagePair("index.html", "text/html"));
	whitelist.push_back(PagePair("favicon.ico", "image/x-icon"));
	whitelist.push_back(PagePair("css/main.css", "text/css"));
	whitelist.push_back(PagePair("css/uni05.ttf","application/x-font-ttf"));
	whitelist.push_back(PagePair("img/hourglass.svg", "image/svg+xml"));
	whitelist.push_back(PagePair("img/logo.svg", "image/svg+xml"));
	whitelist.push_back(PagePair("js/main.js", "text/javascript"));

	bool allowed = false;
	string mime = "";
	for(PagePair page : whitelist)
	{
		if("/" + page.first == resource)
		{
			allowed = true;
			mime = page.second;
		}
	}
	if(allowed)
	{
		type = mime;
		return openFile(viewDir + resource);
	}
	else
	{
		#ifdef _DEBUG
		coutMutex.lock();
		std::cout << "Próba otwarcia nieautoryzowanego pliku: " << resource << std::endl;
		coutMutex.unlock();
		#endif // _DEBUG
		return "";
	}
}

std::string ViewServer::openFile(const std::string& filename)
{
	using namespace std;
	ifstream reqFile(filename, ifstream::in);
    if(!reqFile.good())
    {
        //TODO A może wyjątek tutaj?
		#ifdef _DEBUG
		coutMutex.lock();
		std::cout << "Nie udało się uzyskać zasobu: " << filename << std::endl;
		coutMutex.unlock();
		#endif // _DEBUG
		return "";
    }
    stringstream ss; //Heil Hitler :)
    ss << reqFile.rdbuf();
    reqFile.close();
    return ss.str();
}

bool ViewServer::isClosed()
{
	#ifdef _DEBUG
	coutMutex.lock();
	cout <<"ViewServer::isClosed()"<<endl;
	coutMutex.unlock();
	#endif // _DEBUG
	closedMutex.lock();
	bool b=closed;
	#ifdef _DEBUG
	coutMutex.lock();
	cout <<"closed: "<<closed<<endl;
	coutMutex.unlock();
	#endif // _DEBUG
	closedMutex.unlock();
	return b;
}



























