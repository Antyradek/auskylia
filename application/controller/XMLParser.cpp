/** \file XMLParser.cpp
 * \author Tomasz Jakubczyk
 * \brief Plik z implementacjami metod klasy XMLPareser
 *
 */

#include "XMLParser.hpp"
#include <exception>
#include <iostream>

#include <mutex>
extern std::mutex coutMutex;

/** \brief Klasa opakowująca exception dla XMLParser
 */
struct XMLParserException : std::exception
{
private:
	std::string m;
public:
    /** \brief Wygodny kostruktor wyjątku
     * \param std::string s komunikat do wyświetlenia
     */
	XMLParserException(std::string s)
	{
		m="XMLParserException: "+s+"\n";
	}
    /** \brief przeciążona metoda wyświetla nasz komunikat
     * \return const char* komunikat
     */
	const char* what() const noexcept
	{
		return m.c_str();
	}
};

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

	#ifdef _DEBUG
	coutMutex.lock();
	cout<<"XMLParser::operator() xml: "<<xml<<endl;
	coutMutex.unlock();
	#endif // _DEBUG

	Message* m=new Message();
	/**< \todo zparsować XMLa do Message */

	unsigned int i,j;
	string data("<data>");
	string dataEnd("</data>");
	i=xml.find(data);
	if(i==string::npos)
	{
		throw XMLParserException("i==string::npos");
	}
	j=xml.find(dataEnd);
	if(j==string::npos)
	{
		throw XMLParserException("j==string::npos");
	}
	/**< \todo co, jeśli będzie więcej sekcji data? */
	string s=xml.substr(i,j-i);
	m->msg=s;/**< \todo tak na pewno nie będzie */
	return m;
}
