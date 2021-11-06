#pragma once
#include "Osoba.h"
#include <iostream>
#include <string>

using namespace std;

class Autor : public Osoba
{
public:
	int m_nSifra;
public:
	Autor(string ime, string prezime, int sifra);
	~Autor();
};

