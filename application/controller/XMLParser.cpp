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

	if(xml.size()==0)
	{
		coutMutex.lock();
		cout<<"xml.size()==0"<<endl;
		coutMutex.unlock();
		m->msg="";
		return m;
	}

	unsigned int i,j;
	string data("<data>");
	string dataEnd("</data>");
	i=xml.find(data);
	if(i==string::npos)
	{
		coutMutex.lock();
		cout<<"i==string::npos"<<endl;
		coutMutex.unlock();
		m->msg="";
		return m;
		//throw XMLParserException("i==string::npos");/**< \todo odrzucać wiadomości z niepasującą składnią bez zabijania serwera */
	}
	j=xml.find(dataEnd);
	if(j==string::npos)
	{
		throw XMLParserException("j==string::npos");
	}
	/**< \todo co, jeśli będzie więcej sekcji data? */
	string d=xml.substr(i,j-i);//sekcja data
	string command("<command>");
	string commandEnd("</command>");
	i=d.find(command);
	if(i!=string::npos)
	{
		j=d.find(commandEnd);
		if(j==string::npos)
		{
			throw XMLParserException("j==string::npos");
		}
		string c=d.substr(i,j-i);//sekcja command
		if(c.find("list")!=string::npos)
		{
			m->messageType=MessageType::LIST;
			m->msg=c;
			return m;
		}
		if(c.find("calculate")!=string::npos)
		{
			m->messageType=MessageType::CALCULATE;
			m->msg=d;
			return m;
		}
		if(c.find("status")!=string::npos)
		{
			m->msg=c;
			return m;
		}
		if(c.find("stop")!=string::npos)
		{
			m->msg=c;
			return m;
		}
	}
	m->msg=d;/**< \todo tak na pewno nie będzie */
	return m;
}
