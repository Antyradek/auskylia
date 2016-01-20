#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>

#define DEC2RAD 3.14159265/180

using namespace std;
typedef pair<double, double> Position;

long startTime;

int calcDist(Position& pos1, Position& pos2)
{
	double angle = acos(sin(pos1.first * DEC2RAD) * sin(pos2.first * DEC2RAD) + cos(pos1.first * DEC2RAD) * cos(pos2.first * DEC2RAD) * cos(abs(pos1.second - pos2.second)* DEC2RAD));
	return angle * 6371000;
}

double genPrice(double dist)
{
	default_random_engine generator(startTime++);
	normal_distribution<double> distribution(0.5,0.15);
	double number = distribution(generator);
	normal_distribution<double> priceDist(0,1);
	return dist * 0.002 * number;
}

double genSafety()
{
	default_random_engine generator(startTime++);
	normal_distribution<double> distribution(0.5,0.2);
	double number = distribution(generator);
	if(number < 0) number = 0;
	if(number > 1) number = 1;
}

double genComft()
{
	default_random_engine generator(startTime++);
	normal_distribution<double> distribution(0.5,0.18);
	return distribution(generator);
}

int main()
{
	startTime = chrono::system_clock::now().time_since_epoch().count();
	map<string, Position> ports;
    ifstream airports ("airports.dat");
    if (airports.is_open())
    {
        while ( airports.good() )
        {
			int id;
            string name1;
            string name2;
            string name3;
            string iata;
            string iata2;
            double longitude;
            double latitude;
            airports >> id >> name1 >> name2 >> name3 >> iata >> iata2 >> latitude >> longitude;
            airports.ignore(255, '\n');
			if(iata.compare("\"\"") != 0)
			{
				iata = iata.substr(1,3);
				ports[iata] = Position(latitude, longitude);
				name2 = name2.substr(1, name2.size() - 2);
				name3 = name3.substr(1, name3.size() - 2);
				//cout << name2 << " " << name3 << " " << iata << " " << latitude << " " << longitude << endl;
			}
           
        }
        airports.close();
    }
    ifstream routes ("routes.dat");
	if (routes.is_open())
	{
		while ( routes.good() )
		{
			string air1;
			string air2;
			string iataSrc;
			string iata2;
			string iataDst;
			routes >> air1 >> air2 >> iataSrc >> iata2 >> iataDst;
			routes.ignore(255, '\n');
			int distance = calcDist(ports[iataSrc], ports[iataDst]);
			if(distance != 0)
			{
				//cena zależy od odległości, jest tym samym, co wygoda
				cout << iataSrc << " " << iataDst << " " << genPrice(distance) << " " << genSafety() << " " << genComft() << " " << distance << endl;
			}
			
		}
		routes.close();
	}

}
