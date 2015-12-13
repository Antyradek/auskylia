/** \file ViweServer.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy ViewServer
 *
 */

#include"ViewServer.hpp"
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

ViewServer::ViewServer(int pNo) : portNo(pNo)
{

}

ViewServer::ViewServer() : portNo(8080)
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
	struct sockaddr_in sa;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (-1 == SocketFD)
	{
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
    #ifdef _DEBUG
    std::cout<<"socket utworzony\n";
    #endif // _DEBUG

    memset(&sa, 0, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(portNo);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (-1 == bind(SocketFD,(struct sockaddr *)&sa, sizeof sa))
	{
      perror("bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    #ifdef _DEBUG
    std::cout<<"socket zbindowany\n";
    #endif // _DEBUG

    if (-1 == listen(SocketFD, 10))
	{
      perror("listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    #ifdef _DEBUG
    std::cout<<"nasłuchiwanie\n";
    #endif // _DEBUG

    for (;;)/**< \todo ustalić czas życia gniazda w naszej aplikacji */
	{
		int ConnectFD = accept(SocketFD, NULL, NULL);

		if (0 > ConnectFD)
		{
			perror("accept failed");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}
		#ifdef _DEBUG
		std::cout<<"połączenie zaakceptowane\n";
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
		std::cout<<buf<<std::endl;
		#endif // _DEBUG

		//CROSS_ORIGIN Jest niebezpieczny
		//TODO użyć więcej dobroci c++11 itp a do tego wymyślić naturalny sposób, aby kontroler odpowiadał stroną
		//buf=(char*)"HTTP/1.0 200 OK\n\ntest\0";
		std::string response = "HTTP/1.0 200 OK\nAccess-Control-Allow-Origin: *\n\n<data><response>failture</response><cause>Tymczasowy błąd serwera</cause></data>\0";
		const char* data = response.c_str();
		int len = response.size();
		write(ConnectFD,data,len);
		
		//buf=(char*)str.c_str();
		//write(ConnectFD,buf,siz);

		if (-1 == shutdown(ConnectFD, SHUT_RDWR))
		{
			perror("shutdown failed");
			close(ConnectFD);
			close(SocketFD);
			exit(EXIT_FAILURE);
		}
		close(ConnectFD);
		#ifdef _DEBUG
		std::cout<<"połączenie zakończone\n";
		#endif // _DEBUG

	}

    close(SocketFD);

}
