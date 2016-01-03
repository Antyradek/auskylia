/** \file Message.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy wiadomości
 *
 */

#include "Message.hpp"
#include <iostream>

#include <mutex>
extern std::mutex coutMutex;

using namespace std;

Message::Message()
{
	#ifdef _DEBUG
	coutMutex.lock();
	cout<<"Message::Message()"<<endl;
	coutMutex.unlock();
	#endif // _DEBUG
}

Message::Message(std::string &m) : messageType(NOT_SET)
{
	msg=m;
	#ifdef _DEBUG
	coutMutex.lock();
	cout<<"Message::Message(std::string &m)"<<endl;
	coutMutex.unlock();
	#endif // _DEBUG
}
