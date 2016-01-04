/** \file XMLParser.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy parsera komunikatów XML dla auskylia
 *
 */

#pragma once

#include "Message.hpp"
#include "Command.hpp"
#include <string>

/** \brief Klasa parsera komunikatów XML dla auskylia
 */
class XMLParser
{
public:
	/** Default constructor */
	XMLParser();
	/** Default destructor */
	virtual ~XMLParser();
	Message* operator()(std::string xml);
    /** \brief Przetważa stringa z XML'em na polecenie,
     * czyli najprawdopodobniej ładujemy listę miast do modelu.
     * Wielka szkoda, że nie można przeciążyć tylko zwracanym typem.
     * Istotny jest tylko typ drugiego argumentu, obiecuję, że nie będę go wykożystywał.
     * \param xml std::string
     * \param c Command* Argument potrzebny do użycia drugiej przeciążonej wersji oprtatora.
     * \return Command* Zwracane polecenie, nie zalecam bezmyślenego wysyłania go odrazu do modelu.
     */
	Command* operator()(std::string xml,Command* c);
protected:
private:
};


