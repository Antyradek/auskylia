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
	using namespace std;

	Message* m=new Message();
	/**< \todo zparsować XMLa do Message */

	unsigned int i,j;
	string data("<data>");
	string dataEnd("</data>");
	i=xml.find(data);
	j=xml.find(dataEnd);
	/**< \todo obsługa string::npos */
	/**< \todo co, jeśli będzie więcej sekcji data? */
	string s=xml.substr(i,j-i);
	m->msg=s;/**< \todo tak na pewno nie będzie */
	return m;
}
