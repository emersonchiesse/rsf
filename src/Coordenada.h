#ifndef COORDENADA_H
#define COORDENADA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

using namespace std;

class Coordenada
{
private:
	float lat;
	float longitude;
	int altitude;


public:
	Coordenada() {};
	Coordenada(string _lat, string _lon)
	{
		lat = 0;
		longitude = 0;
		altitude = 0;
	}

	int getAltitude();

};
#endif
