/** \file Event.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy Event
 *
 */

#pragma once

#include <mutex>
extern std::mutex coutMutex;

/** \brief typy zdarzeń
 */
enum EventType
{
    Test,
    SHUT_DOWN,
    MESSAGE_FROM_VIEW_SERVER,
    MESSAGE_FROM_MODEL
};

/** \brief Klasa reprezentująca zdarzenie.
 * Na rzecz szybkiego uzyskania działania aplikacji rezygnuję z pomysłu zrobienia
 * tej klasy wirtualną, gdyż powstaną przy tym ogromne niepoptrzebne problemy.
 */
class Event
{
public:
    Event() : type(Test), data(nullptr)
    {

    }
    Event(EventType t) : type(t), data(nullptr)
    {

    }
    Event(EventType t, void* d) : type(t), data(d)
    {

    }
    ~Event()
    {
		#ifdef _DEBUG
		coutMutex.lock();
		std::cout<<"~Event "<<type<<" "<<data<<"\n";
		coutMutex.unlock();
		#endif // _DEBUG
    }
    EventType type;/**< typ zdarzenia pozwala wybrać właściwą metodę do jego obsługi */
    void* data;/**< dane niezbednę do zrealizowania metody obsługującej zdarzenie */
};
