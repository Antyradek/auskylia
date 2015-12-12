/** \file XMLParser.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy XMLPareser
 *
 */

#include "XMLParser.hpp"

XMLParser::XMLParser()
{
	//ctor
}

XMLParser::~XMLParser()
{
	//dtor
}

Message* XMLParser::operator()(std::string xml)
{
	Message* m=new Message();
	/**< \todo zparsować XMLa do Message */
	return m;
}
