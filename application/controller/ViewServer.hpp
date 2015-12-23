/** \file ViewServer.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy serwera widoku.
 *
 */

#pragma once

#include "BlockingQueue.hpp"
#include "Event.hpp"

class ViewServer
{
public:
	ViewServer(int);
	ViewServer();
	~ViewServer();
    /** \brief Metoda tworzy gniazdo, odbiera zapytanie i odsyła odpowiedź
     * dane do odpowiedzi może dostawać różnie, jak będę się nad tym dokładniej zastanawiał,
     * to ustalę jak to będzie działać
     * \return void
     */
	void listenAndRespond();
	void setControllerBlockingQueue(BlockingQueue<Event*>* q);
private:
	int portNo;
	/** \todo ustalić najwygodniejszy sposób na uzyskiwanie odpowiedzi z kontrolera
	 * i modelu. może to będzie condition z jakimś timeoutem, czy co
	 */
	 BlockingQueue<Event*>* controllerBlockingQueue;
};
