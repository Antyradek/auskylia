/** \file Command.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy Command.
 *
 */

#include "Command.hpp"
#include <iostream>

//using namespace CommandType;
using namespace std;

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
		#ifdef _DEBUG
		cout<<"price: "<<price<<endl;
		#endif // _DEBUG
		safety=m->safety;
		#ifdef _DEBUG
		cout<<"safety: "<<safety<<endl;
		#endif // _DEBUG
		comfort=m->comfort;
		#ifdef _DEBUG
		cout<<"comfort: "<<comfort<<endl;
		#endif // _DEBUG
		time=m->time;
		#ifdef _DEBUG
		cout<<"time: "<<time<<endl;
		#endif // _DEBUG
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











