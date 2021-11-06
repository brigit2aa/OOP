#include "Knjiga.h"

Knjiga::Knjiga(int rb, int sifra, string naziv, string autor, int gi, string nakl, Citatelj *oCitatelj, vector<Autor*> vAutori)
{
	m_nRbr = rb;
	m_nsifra = sifra;
	m_sNaziv = naziv;
	m_sAutori = autor;
	m_nGodinaIzdanja = gi;
	m_sNakladnik = nakl;
	/*if (m_oCitatelj != nullptr)
	{
		*m_oCitatelj = *oCitatelj;
	}*/
	if (m_oCitatelj == nullptr) 
	{
		m_oCitatelj = oCitatelj;
	}
	m_vAutori = vAutori;
}

Knjiga::~Knjiga()
{

}

vector<Autor*> Knjiga::DajVektorAutor() {
	return m_vAutori;
}

string Knjiga::DajNakladnik() {
	return m_sNakladnik;
}

int Knjiga::DajGodIzd() {
	return m_nGodinaIzdanja;
}

int Knjiga::DajCitatOib() {
	return m_oCitatelj->DajOib();
}

string Knjiga::DajAutor() {
	return m_sAutori;
}

string Knjiga::DajNaziv() {
	return m_sNaziv;
}

int Knjiga::DajSifru() {
	return m_nsifra;
}


int Knjiga::DajRb() {
	return m_nRbr;
}


int Knjiga::DajId() {
	return m_nsifra;
}