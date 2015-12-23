/** \file Message.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy wiadomości
 *
 */

#pragma once

#include <string>

/** \brief klasa wiadomości
 */
class Message
{
public:
	/** Default constructor */
	Message();
	Message(std::string &m);
	std::string msg;/**< \todo przemyśleć typ */
protected:
private:
};
