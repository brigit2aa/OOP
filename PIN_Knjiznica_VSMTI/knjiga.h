#pragma once
#include <iostream>
#include <string>
#include "Citatelj.h"
#include <vector>
#include "Autor.h"

using namespace std;
class Knjiga
{
public:
	int m_nRbr;
	int m_nsifra;
	string m_sNaziv;
	string m_sAutori;
	int m_nGodinaIzdanja;
	string m_sNakladnik;
	Citatelj *m_oCitatelj;
	vector<Autor*> m_vAutori;

	int DajId();
	int DajRb();
	int DajSifru();
	string DajNaziv();
	string DajAutor();
	int DajGodIzd();
	string DajNakladnik();
	int DajCitatOib();
	vector<Autor*> DajVektorAutor();

public:
	
	Knjiga(int rb, int sifra, string naziv, string autor, int gi, string nakl, Citatelj *oCitatelj, vector<Autor*> vAutori);
	~Knjiga();

};

