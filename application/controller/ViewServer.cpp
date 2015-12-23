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

ViewServer::ViewServer(int pNo) : portNo(pNo), controllerBlockingQueue(nullptr)
{

}

//TODO ten konstruktor chyba się nigdy nie wywyołuje, bo domyślny port jest zapsany w main i wywyołuje powyższy. Można to chyba usunąć.
ViewServer::ViewServer() : portNo(5005), controllerBlockingQueue(nullptr)
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
    std::cout<<"Połączenie sukcesywne\n";
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

    for (;;)/**< \todo ustalić czas życia gniazda w naszej aplikacji */
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
		if(msg.size()==0)//z jakiegoś powodu zdażają się puste połączenia
		{
			Message* message;
			message=xmlParser(msg);
			Event* e=new Event(MESSAGE_FROM_VIEW_SERVER,(void*)message);
			controllerBlockingQueue->push_back(e);
		}

		//TODO użyć więcej dobroci c++11 itp a do tego wymyślić naturalny sposób, aby kontroler odpowiadał stroną i nie był podatny na cofanie się w ścieżce (wpisywanie /../)
		//buf=(char*)"HTTP/1.0 200 OK\n\ntest\0";
		std::string response = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\n\n<data><response>failture</response><cause>Ta funkcja jeszcze nie jest gotowa.</cause></data>\0";
		const char* data = response.c_str();
		int len = response.size();
		write(ConnectFD,data,len);

		//buf=(char*)str.c_str();
		//write(ConnectFD,buf,siz);

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


















