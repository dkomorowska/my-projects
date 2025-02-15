#include <string.h>
#include "instrumenty.hpp"

using namespace std;


//************metody klasy towar************
instrument::instrument()
{
	strcpy(nazwa," ");
	strcpy(model, " ");
    strcpy(marka, " ");
    strcpy(rodzaj, " ");
	cena=0;
	waga=0;
	sztuk=0;
}


instrument::instrument(char* mod, char* mar, char* rodz, char *naz, float cen, float wag, int szt)
{
	strcpy(nazwa,naz);
	strcpy(model, mod);
    strcpy(marka, mar);
    strcpy(rodzaj, rodz);
	cena=cen;
	sztuk=szt;
	waga=wag;
}


void instrument::czysc()
{
	strcpy(nazwa," ");
	strcpy(model, " ");
    strcpy(marka, " ");
    strcpy(rodzaj, " ");
	cena=0;
	sztuk=0;
	waga=0;
}


void instrument::setNazwa(char *naz)
{
	strcpy(nazwa, naz);
}

void instrument::setModel(char* mod) 
{
    strcpy(model, mod);
}

void instrument::setMarka(char* mar) 
{
    strcpy(marka, mar);
}

void instrument::setRodzaj(char* rodz) 
{
    strcpy(rodzaj, rodz);
}

bool instrument::setCena(float cena)
{
	if (cena>0)
	{
		this->cena=cena;
		return 1;
	}
	else
	{
		return 0;
	}
}

bool instrument::setWaga(float waga) 
{
    if (waga > 0) 
	{
        this->waga=waga;
        return true;
    }
    return false;
}

void instrument::setSztuk(int szt)
{
	sztuk=szt;
}


void instrument::pobierz(char *naz, char* mod, char* mar, char* rodz, float cen, float wag, int szt)
{
	strcpy(nazwa,naz);
	strcpy(model,mod);
    strcpy(marka,mar);
    strcpy(rodzaj,rodz);
	cena=cen;
	sztuk=szt;
	waga=wag;
}


char* instrument::getNazwa()
{
	return nazwa;
}

char* instrument::getModel() 
{
    return model;
}

char* instrument::getMarka() 
{
    return marka;
}

char* instrument::getRodzaj() 
{
    return rodzaj;
}

float instrument::getCena()
{
	return cena;
}

float instrument::getWaga() 
{
    return waga;
}

int instrument::getSztuk()
{
	return sztuk;
}

float instrument::wartosc()
{
	return cena*sztuk;
}

	void instrument::setZaznaczony(bool status)
{
    zaznaczony = status;
}

bool instrument::getZaznaczony()
{
    return zaznaczony;
}

void instrument::zmianaZaznaczony()
{
    zaznaczony = !zaznaczony;  // przełącza flagę
}
	
