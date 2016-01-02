/** \file Message.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy wiadomości
 *
 */

#pragma once

#include <string>

enum MessageType
{
	LIST,
	CALCULATE
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
protected:
private:
};
