// #include "stdafx.h"
#include <iostream>

using namespace std;

class Televisore
{
private:
    bool inclassAcceso;
    int inclassVolume;
    int inclassCanale;
    bool inclassSilenzioso;

public:
    Televisore();
    Televisore(int, int);
    ~Televisore();
    
    bool getAcceso();
    int getVolume();
    int getCanale();
    bool getSilenzioso();
    
    void pulsanteRosso();
    void canaleSuccessivo();
    void canalePrecedente();
    void aumentaVolume();
    void abbassaVolume();
    void impostaCanale(int);
    void pulsanteSilenzioso();
};

Televisore::Televisore()
{
	inclassAcceso = false;
    inclassVolume = 0;
	inclassCanale = 0;
	inclassSilenzioso = false;
}

Televisore::Televisore(int volume, int canale)
{
	inclassAcceso = false;
    inclassVolume = volume;
	inclassCanale = canale;
	inclassSilenzioso = false;
}

Televisore::~Televisore()
{
	
}

bool Televisore::getAcceso()
{
	return inclassAcceso;
}

int Televisore::getVolume()
{
	return inclassVolume;
}

int Televisore::getCanale()
{
	return inclassCanale;
}

bool Televisore::getSilenzioso()
{
	return inclassSilenzioso;
}

void Televisore::pulsanteRosso()
{
	if(inclassAcceso == true)
		inclassAcceso = false;
	else
		inclassAcceso = true;
}

void Televisore::canaleSuccessivo()
{
	inclassCanale = inclassCanale + 1;
	if(inclassCanale > 99)
		inclassCanale = 0;
}

void Televisore::canalePrecedente()
{
	inclassCanale = inclassCanale - 1;
	if(inclassCanale < 0)
		inclassCanale = 99;
}

void Televisore::aumentaVolume()
{
	inclassVolume = inclassVolume + 1;
	if(inclassVolume > 10)
		inclassVolume = 10;
}

void Televisore::abbassaVolume()
{
	inclassVolume = inclassVolume - 1;
	if(inclassVolume < 0)
		inclassVolume = 0;
}

void Televisore::impostaCanale(int canale)
{
	if(canale >=0 && canale <=99)
		inclassCanale = canale;
}

void Televisore::pulsanteSilenzioso()
{
	if(inclassSilenzioso == true)
		inclassSilenzioso = false;
	else {
		inclassSilenzioso = true;
		inclassVolume = 0;
	}
}


