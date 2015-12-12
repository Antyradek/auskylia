/** \file XMLParser.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy parsera komunikatów XML dla auskylia
 *
 */

#pragma once

#include "Message.hpp"
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
protected:
private:
};


