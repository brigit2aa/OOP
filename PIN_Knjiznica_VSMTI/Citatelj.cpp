#include "Citatelj.h"
Citatelj::Citatelj(string ime, string prezime, int oib, string adresa, string zakasnina) : Osoba(ime, prezime)
{
	m_nOib = oib;
	m_sAdresa = adresa;
	m_sZakasnina = zakasnina;
}
Citatelj::~Citatelj()
{

}
int Citatelj::DajOib() {
	return m_nOib;
}