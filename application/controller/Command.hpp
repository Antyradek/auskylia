/** \file Command.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy polecenia do modelu.
 *
 */

#pragma once

#include "Message.hpp"

namespace CommandType
{
	enum CommandType
	{
		START,
		STOP,
		STATUS
	};
}

/** \brief Klasa polecenia do modelu
 */
class Command
{
public:
	Command(CommandType::CommandType t);
	CommandType::CommandType commandType;
	//parametry wykonania algorytmu
	std::string start;
	std::string end;
	std::string price;
	std::string safety;
	std::string comfort;
	std::string time;
	void copyCalculateMessageData(Message* m);
};
