/** \file Controller.hpp
 * \author Tomasz Jakubczyk
 * \brief Plik nagłówkowy klasy kontrolera.
 *
 */

#pragma once

#include "../model/Model.hpp"
#include "ViewServer.hpp"

class Controller
{
public:
	Controller();
	~Controller();
	void setModel(Model* m);
	void setViewServer(ViewServer* v);
	void start();
private:
	Model* model;
	ViewServer* viewServer;
	bool shutDown;
	/**< \todo być może będzie tu BlockingQueue */
};
