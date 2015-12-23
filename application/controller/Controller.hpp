/** \file Controller.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy kontrolera.
 *
 */

#pragma once

#include "../model/Model.hpp"
#include "ViewServer.hpp"
#include "BlockingQueue.hpp"
#include "Event.hpp"

class Controller
{
public:
	Controller();
	~Controller();
	void setModel(Model* m);
	void setViewServer(ViewServer* v);
	void start();
	void setup();/**< ustawienie kolejki blokującej */
	void triggerShutDown();
private:
	Model* model;
	ViewServer* viewServer;
	bool shutDown;
    /** \brief kolejka zdażeń przetwarzana przez kontroler
     */
	BlockingQueue<Event*>* controllerBlockingQueue;
};
