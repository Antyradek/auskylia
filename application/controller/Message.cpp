/** \file Message.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy wiadomości
 *
 */

#include "Message.hpp"

Message::Message()
{
	//ctor
}

Message::Message(std::string &m)
{
	msg=m;
}
