#include "Autor.h"
Autor::Autor(string ime, string prezime, int sifra) : Osoba(ime, prezime)
{
	m_nSifra = sifra;
}
Autor::~Autor()
{

}