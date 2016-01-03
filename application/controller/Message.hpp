/** \file Message.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy wiadomości
 *
 */

#pragma once

#include <string>

enum MessageType
{
	NOT_SET,
	LIST,
	CALCULATE,
	STATUS,
	STOP
};

/** \brief klasa wiadomości
 */
class Message
{
public:
	/** Default constructor */
	Message();
	Message(std::string &m);
	MessageType messageType;
	std::string msg;/**< \todo przemyśleć typ */
	//pola dla calculate
	std::string start;
	std::string end;
	std::string price;
	std::string safety;
	std::string comfort;
	std::string time;
protected:
private:
};
