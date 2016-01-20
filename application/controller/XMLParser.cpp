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

using namespace std;

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

	#ifdef _DEBUG2
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

	unsigned int i,j,k,l;
	string data("<data>");
	string dataEnd("</data>");
	i=xml.find(data);
	if(i==string::npos)
	{
		coutMutex.lock();
		cout<<"data i==string::npos"<<endl;
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

			k=d.find("<start>");
			if(k==string::npos) throw XMLParserException("<start>k==string::npos");
			k+=7;
			l=d.find("</start>");
			if(l==string::npos) throw XMLParserException("</start>l==string::npos");
            m->start=d.substr(k,l-k);

            k=d.find("<end>");
			if(k==string::npos) throw XMLParserException("<end>k==string::npos");
			k+=5;
			l=d.find("</end>");
			if(l==string::npos) throw XMLParserException("</end>l==string::npos");
            m->end=d.substr(k,l-k);

            k=d.find("<price>");
			if(k==string::npos) throw XMLParserException("<price>k==string::npos");
			k+=7;
			l=d.find("</price>");
			if(l==string::npos) throw XMLParserException("</price>l==string::npos");
            m->price=d.substr(k,l-k);

            k=d.find("<safety>");
			if(k==string::npos) throw XMLParserException("<safety>k==string::npos");
			k+=8;
			l=d.find("</safety>");
			if(l==string::npos) throw XMLParserException("</safety>l==string::npos");
            m->safety=d.substr(k,l-k);

            k=d.find("<comfort>");
			if(k==string::npos) throw XMLParserException("<comfort>k==string::npos");
			k+=9;
			l=d.find("</comfort>");
			if(l==string::npos) throw XMLParserException("</comfort>l==string::npos");
            m->comfort=d.substr(k,l-k);

            k=d.find("<time>");
			if(k==string::npos) throw XMLParserException("<time>k==string::npos");
			k+=9;
			l=d.find("</time>");
			if(l==string::npos) throw XMLParserException("</time>l==string::npos");
            m->time=d.substr(k,l-k);

			return m;
		}
		if(c.find("status")!=string::npos)
		{
			m->msg=c;
			m->messageType=MessageType::STATUS;
			return m;
		}
		if(c.find("stop")!=string::npos)
		{
			m->msg=c;
			m->messageType=MessageType::STOP;
			return m;
		}
	}
	else
	{
		string response("<response>");
		string responseEnd("</response>");
		i=d.find(response);
		if(i!=string::npos)
		{
			j=d.find(responseEnd);
			if(j==string::npos)
			{
				throw XMLParserException("responseEnd j==string::npos");
			}
			string c=d.substr(i,j-i);
			if(c.find("list")!=string::npos)
			{
				m->messageType=MessageType::LIST;
				m->msg=c;
				throw XMLParserException("Czemu próbujesz parsować XML'a z odpowiedzią do widoku na wiadomość z widoku? Być może miałeś na myśli inną wersję przeciążonego XMLParser::operator() ?");
				return m;
			}
		}
	}
	m->msg=d;/**< \todo tak na pewno nie będzie */
	return m;
}

Command* XMLParser::operator()(std::string xml,Command* c)
{
	#ifdef _DEBUG2
	coutMutex.lock();
	cout<<"XMLParser::operator()(std::string xml,Command* c) xml: "<<xml<<endl;
	coutMutex.unlock();
	#endif // _DEBUG

	Command* m=new Command(CommandType::START);

	if(xml.size()==0)
	{
		coutMutex.lock();
		cout<<"xml.size()==0"<<endl;
		coutMutex.unlock();
		//m->msg="";
		return m;
	}

	unsigned int i,j,k,l;
	string data("<data>");
	string dataEnd("</data>");
	i=xml.find(data);
	if(i==string::npos)
	{
		coutMutex.lock();
		cout<<"data i==string::npos"<<endl;
		coutMutex.unlock();
		//m->msg="";
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
		throw XMLParserException("Probujesz użyć złej wersji parsera, ta wersja przetważa XML do poleceń dla modelu, a nie na wiadomości do widoku.");
	}
}
