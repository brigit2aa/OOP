#pragma once
#include "Osoba.h"
class Citatelj : public Osoba
{ 
public:
	int m_nOib;
	string m_sAdresa;
	string m_sZakasnina;
	int DajOib();
public:
	Citatelj(string ime, string prezime, int oib, string adresa, string zakasnina);
	~Citatelj();
};

