#pragma once
#include <iostream>
#include <string>
#include "Autor.h"
#include "Citatelj.h"
#include "knjiga.h"
#include "Osoba.h"
#include "tinyxml2.h"
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
using namespace tinyxml2;

class Main_Knjiznica
{
public:
	Main_Knjiznica();
	~Main_Knjiznica();

	vector<Knjiga*> vKnjiga;
	bool UcitajXmlKnjige();
	void DajSveKnjige();

	vector<Autor*> vAutor;
	bool UcitajXmlAutore();
	void DajAutore();

	vector<Citatelj*> vCitatelj;
	bool UcitajXmlCitatelje();
	void DajSveCitatelje();

	bool UcitajXmlZapise();

	Citatelj* PronadjiCitateljaPoOibu(int oib);
	Knjiga* PronadjiKnjiguPoOibu(double oib);
	Autor* PronadjiAutoraPoSifri(int sifra);
	void UnosNoveKnjige();
	void PosudiKnjigu();
	void VratiKnjigu();
	void ObrisiKnjigu();
	void UpisKnjigaXML();
	void SpremiCvor(Knjiga* knjiga);//spremanje jedne po jedne knjige u datoteku
	Citatelj* PronadiCitatelja(int m_nOib);
	void ObrisiXml(int StariId,int oibCitatelja);
	void PromjeniXml(double a, int b, int sifraAutora);
	void BrisanjePodataka();
};