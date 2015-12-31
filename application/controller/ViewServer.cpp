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
	portNo(pNo),
	controllerBlockingQueue(nullptr),
	shutDown(false)
{

}

//TODO ten konstruktor chyba się nigdy nie wywyołuje, bo domyślny port jest zapsany w main i wywyołuje powyższy. Można to chyba usunąć.
ViewServer::ViewServer() :
	portNo(5005),
	controllerBlockingQueue(nullptr),
	shutDown(false)
{

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
		#ifdef _DEBUG
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
		#ifdef _DEBUG
		coutMutex.lock();
		cout << "Zapytano się o stronę: " << reqDoc << endl;
		coutMutex.unlock();
		#endif // _DEBUG

		string body = "";
		string header = "HTTP/1.1 200 OK\n\n";
		if(reqDoc == "/server")
		{
			//to zapytanie do serwera, parsujemy XML i generujemy odpowiedź

			//TODO Testowo
			body = "<data><response>failture</response><cause>Ta funkcja jeszcze nie jest gotowa.</cause></data>";
			//jakieś dziwne rzeczy się działy z poniższym if'em
			if(true/*msg.size()==0*/)//z jakiegoś powodu zdażają się puste połączenia
			{
				Message* message=nullptr;
				message=xmlParser(msg);
				Event* e=new Event(MESSAGE_FROM_VIEW_SERVER,(void*)message);
				controllerBlockingQueue->push_back(e);
			}
		}
		else
		{
			//zapytanie o zasoby, musimy zwrócić stronę internetową
			body = getPage(reqDoc);
		}

		string response = header + body;
		const char* data = response.c_str();
		int len = response.size();
		write(ConnectFD,data,len);

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

}

void ViewServer::setControllerBlockingQueue(BlockingQueue<Event*>* q)
{
	controllerBlockingQueue=q;
}

void ViewServer::triggerShutDown()
{
	shutDown=true;
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

std::string ViewServer::getPage(std::string resource)
{
	std::string viewDir = "../view";

	if(resource == "/")
	{
		resource = "/index.html";
	}

	//hiperbezpieczna i hiperniewygodna metoda
	std::vector<std::string> whitelist;
	whitelist.push_back("index.html");
	whitelist.push_back("favicon.ico");
	whitelist.push_back("css/main.css");
	whitelist.push_back("css/uni05.ttf");
	whitelist.push_back("img/hourglass.svg");
	whitelist.push_back("img/logo.svg");
	whitelist.push_back("js/main.js");

	bool allowed = false;
	for(std::string page : whitelist)
	{
		if("/" + page == resource)
		{
			allowed = true;
		}
	}
	if(allowed)
	{
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
