/** \file Command.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Command.
 *
 */

#include "Command.hpp"

//using namespace CommandType;

Command::Command(CommandType::CommandType t) : commandType(t)
{

}

void Command::copyCalculateMessageData(Message* m)
{
	if(m==nullptr)
	{
		cout<<"Command::copyCalculateMessageData(Message* m) m==nullptr"<<endl;
	}
	if(m->messageType==MessageType::CALCULATE)
	{
		start=m->start;
		end=m->end;
		price=m->price;
		safety=m->safety;
		comfort=m->comfort;
		time=m->time;
	}
	else if(m->messageType==MessageType::LIST)
	{
		/**< \todo kod kopiowania listy miast jeszcze nie napisany */
		cout<<"kod kopiowania listy miast jeszcze nie napisany"<<endl;
	}
	else
	{
		cout<<"próbujesz skopiować dane z wiadomości nieodpowiedniego typu: "<<m->messageType<<endl;
	}
}











