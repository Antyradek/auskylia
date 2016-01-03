/** \file Command.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy polecenia do modelu.
 *
 */

#pragma once

enum CommandType
{
	START,
	STOP,
	STATUS
};

/** \brief Klasa polecenia do modelu
 */
class Command
{
public:
	Command(CommandType t);
	CommandType commandType;
};
