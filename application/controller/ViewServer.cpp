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

ViewServer::ViewServer(int pNo) : portNo(pNo)
{

}

ViewServer::ViewServer() : portNo(8080)
{

}

void ViewServer::listenAndRespond()
{
	struct sockaddr_in sa;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (-1 == SocketFD)
	{
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }

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

    if (-1 == listen(SocketFD, 10))
	{
      perror("listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    for (;;)/**< \todo ustalić czas życia gniazda w naszej aplikacji */
	{
		int ConnectFD = accept(SocketFD, NULL, NULL);

		if (0 > ConnectFD)
		{
			perror("accept failed");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}

		/**< \todo zczytać zapytanie od widoku */
		/**< \todo odesłać odpowiedź z nagłówkiem HTTP */
		/* perform read write operations ...
		read(ConnectFD, buff, size)
		*/

		if (-1 == shutdown(ConnectFD, SHUT_RDWR))
		{
			perror("shutdown failed");
			close(ConnectFD);
			close(SocketFD);
			exit(EXIT_FAILURE);
		}
		close(ConnectFD);
	}

    close(SocketFD);

}
