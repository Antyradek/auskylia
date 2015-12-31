/** \file ViewServer.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy serwera widoku.
 *
 */

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
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
	void triggerShutDown();
private:
	int portNo;
	/** \todo ustalić najwygodniejszy sposób na uzyskiwanie odpowiedzi z kontrolera
	 * i modelu. może to będzie condition z jakimś timeoutem, czy co
	 */
	 BlockingQueue<Event*>* controllerBlockingQueue;
	 bool shutDown;
	 /** \brief Czy podane zapytanie jest zapytaniem serwera, czy zapytaniem o stronę internetową.
	  * \return Strona podana w nagłówku
	  */
	 std::string getPageRequest(const std::string& message);
	 /** \brief Zwraca żądaną stronę internetową, jeśli jest dozwolona, lub pustkę, jeśli nie jest
	  */
	 std::string getPage(std::string resource);
	 /** \brief Otwiera i zwraca zawartość pliku. Bez żadnej kontroli
	 */
	 std::string openFile(const std::string& filename);
};
