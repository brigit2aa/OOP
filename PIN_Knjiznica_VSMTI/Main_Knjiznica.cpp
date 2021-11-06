#include "Main_Knjiznica.h"

Main_Knjiznica::Main_Knjiznica()
{
	UcitajXmlAutore();
	UcitajXmlCitatelje();
	UcitajXmlKnjige();
}
bool Main_Knjiznica::UcitajXmlAutore()
{
	string m_sAdresa;
	
	
	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("autori.xml");
	if (oResult != XML_SUCCESS)
	{
		cout << "Greška u XML datoteci!" << endl;
		return false;
	}
	XMLNode* pRoot = oDoc.FirstChildElement("autorixm");
	if (pRoot == nullptr) return false;
	
	XMLElement* oKnjiga = pRoot->FirstChildElement("Autori");
	if (oKnjiga == nullptr) return false;
	for (XMLElement* pChild = oKnjiga->FirstChildElement("Autor"); pChild != NULL; pChild = pChild->NextSiblingElement())
	{
		//XML podaci imaju zapis: <ime prezime sifra>
		string m_sIme = pChild->Attribute("ime");
		string m_sPrezime = pChild->Attribute("prezime");
		int m_nSifra = atoi(pChild->Attribute("sifra"));
		this->vAutor.push_back(new Autor(m_sIme, m_sPrezime, m_nSifra ));
	}
	return true;
}
bool Main_Knjiznica::UcitajXmlCitatelje()
{
	;
	string m_sAdresa;

	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("citatelji.xml");
	if (oResult != XML_SUCCESS)
	{
		cout << "Greška u XML datoteci!" << endl;
		return false;
	}
	XMLNode* pRoot = oDoc.FirstChildElement("citateljixm");
	if (pRoot == nullptr) return false;
	//Citatelj
	XMLElement* oCitatelj = pRoot->FirstChildElement("Citatelji");
	if (oCitatelj == nullptr) return false;
	for (XMLElement* pChild = oCitatelj->FirstChildElement("Citatelj"); pChild != NULL; pChild = pChild->NextSiblingElement())
	{
		//XML podaci imaju zapis: <ime prezime oib adresa zakasnina>
		string m_sIme = pChild->Attribute("ime");
		string m_sPrezime = pChild->Attribute("prezime");
		int m_nOib = atoi(pChild->Attribute("oib"));
		string m_sAdresa = pChild->Attribute("adresa");
		string m_sZakasnina = pChild->Attribute("zakasnina");
		this->vCitatelj.push_back(new Citatelj(m_sIme, m_sPrezime, m_nOib, m_sAdresa, m_sZakasnina));
	}

	return true;
}
bool Main_Knjiznica::UcitajXmlKnjige()
{
	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("knjige.xml");
	if (oResult != XML_SUCCESS)
	{
		cout << "Greška u XML datoteci!" << endl;
		return false;
	}
	XMLNode* pRoot = oDoc.FirstChildElement("knjigexm");
	if (pRoot == nullptr) return false;
	//Citatelji
	XMLElement* oCitatelj = pRoot->FirstChildElement("Knjige");
	if (oCitatelj == nullptr) return false;

	for (XMLElement* pChild = oCitatelj->FirstChildElement("Knjiga"); pChild != NULL; pChild = pChild->NextSiblingElement())
	{
		//XML podaci imaju zapis: <r.broj oib_citatelja sifra naziv autori>

		if (pChild == nullptr) {
			cout << "PChild is a null pointer" << endl;
		}
		
		int m_nRbr = atoi(pChild->Attribute("r.broj"));
		int m_nOib = atoi(pChild->Attribute("oib_citatelja"));
		int m_nsifra = stoi(pChild->Attribute("sifra"));
		string m_sNaziv = pChild->Attribute("naziv");
		string m_sAutori = pChild->Attribute("autori");
		std::string str = "autori";
		std::vector<int> vect;
		std::stringstream ss(pChild->Attribute("autori"));
		vector<Autor*> vAut;

		for (int i; ss >> i;)
		{
			vect.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}
		for (int i = 0; i < vect.size(); i++) 
		{
			vAut.push_back((PronadjiAutoraPoSifri(vect[i])));
		}
		Citatelj* citatelj=PronadiCitatelja(m_nOib);
		int m_nGodinaIzdanja = atoi(pChild->Attribute("godina_izdanja"));
		string m_sNakladnik = pChild->Attribute("nakladnik");
		this->vKnjiga.push_back(new Knjiga(m_nRbr, m_nsifra, m_sNaziv, m_sAutori, m_nGodinaIzdanja, m_sNakladnik, citatelj, vAut));	
	}
	return true;
}

bool Main_Knjiznica::UcitajXmlZapise()
{
	XMLDocument oDoc;
	XMLError oResult = oDoc.LoadFile("Podaci.xml");
	if (oResult != tinyxml2::XML_SUCCESS) return false;
	XMLNode* pRoot = oDoc.FirstChildElement("knjigexm");
	if (pRoot == nullptr) return false;
	//Zapisi
	XMLElement* oZapis = pRoot->FirstChildElement("oib_citatelja");
	if (oZapis == nullptr) return false;
	for (XMLElement* pChild = oZapis->FirstChildElement("Knjiga"); pChild != NULL; pChild = pChild->NextSiblingElement())
	{
		
		int m_nKnjigaOib = atoi(pChild->Attribute("oib_citatelja"));
		double m_nCitateljOib = atof(pChild->Attribute("oib"));
		//U zapisu imamo oib koji se nalazi u citatelj.xml te oib citatelja koji se nalazi u datoteci knjig.xml,
		//prema oib-ovima moramo pronaci konkretan objekt
		//Kreiramo privremene pokazivace *oCitatelj i *oKnjiga pozivom funkcija
		//Funkcije vracaju konkretne objekte koje smo ucitali u vektore
		//Novokreirane pokazivace odmah usmjerimo na konkretne objekte
		//S pokazivacima radimo kao da radimo sa konkretnim objektima
		Citatelj* oCitatelj = this->PronadjiCitateljaPoOibu(m_nCitateljOib);
		Knjiga* oKnjiga = this->PronadjiKnjiguPoOibu(m_nKnjigaOib);
		//Ako smo pronasli konkretne objekte putem pokazivaca azuriramo podatkovni clan klase Citatelj
		if (oCitatelj != nullptr && oKnjiga != nullptr)
		{
			oKnjiga->m_oCitatelj = oCitatelj;
		}

	}
	return true;
}
void Main_Knjiznica::DajAutore()
{
	cout << "\n[------------A U T O R I------------]" << endl;
	for (int i = 0; i < vAutor.size(); i++) {
		cout << "Sifra: " << vAutor[i]->m_nSifra << " Ime: " << vAutor[i]->m_sIme << " Prezime: " << vAutor[i]->m_sPrezime << endl;
	}
}
void Main_Knjiznica::DajSveCitatelje()
{
	cout << "\n[------------C I T A T E LJ I------------]" << endl;
	for (int i = 0; i < vCitatelj.size(); i++)
	{
		cout << "Ime: " << vCitatelj[i]->m_sIme << " Prezime: " << vCitatelj[i]->m_sPrezime << " OIB: " << vCitatelj[i]->DajOib() << " Adresa: " << vCitatelj[i]->m_sAdresa << " Zakasnina: " << vCitatelj[i]->m_sZakasnina << endl;
	}
}
void Main_Knjiznica::DajSveKnjige()
{
	cout << "\n[------------K NJ I G E------------]" << endl;
	for (int i = 0; i < vKnjiga.size(); i++)
	{
		if (vKnjiga[i]->m_oCitatelj != nullptr) //Ako je pokazivac na knjigu razlicit od nullptr onda je knjiga posudjena
		{
			if(vKnjiga[i]->m_oCitatelj->m_nOib != 1){///
			cout << "R.br: " << vKnjiga[i]->DajRb() << " Sifra: " << vKnjiga[i]->DajSifru() << " Naziv: " << vKnjiga[i]->DajNaziv() << " Godina izdanja: " << vKnjiga[i]->DajGodIzd() << " Nakladnik: " << vKnjiga[i]->DajNakladnik() << " Status knjige: Knjiga je posudena!"<< endl;
			cout << "Autori knjige: " << endl;
			for (int j = 0; j < vKnjiga[i]->m_vAutori.size(); j++) {
				cout << "Ime i prezime autora: " << vKnjiga[i]->m_vAutori[j]->m_sIme << vKnjiga[i]->m_vAutori[j]->m_sPrezime << endl;
			}
		}
		}
		
		else if(vKnjiga[i]->m_oCitatelj == nullptr) //U suprotnom umjesto oib citatelj ispisujemo tekst " Status knjige: Knjiga nije posudjena!"
		{
			cout << "R.br: " << vKnjiga[i]->m_nRbr << " Sifra: " << vKnjiga[i]->m_nsifra << " Naziv: " << vKnjiga[i]->m_sNaziv<< " Godina izdanja: " << vKnjiga[i]->m_nGodinaIzdanja << " Nakladnik: " << vKnjiga[i]->m_sNakladnik << " Status knjige: Knjiga nije posudjena!" << endl;
			for (int j = 0; j < vKnjiga[i]->m_vAutori.size(); j++) {
				cout << "Ime i prezime autora: " << vKnjiga[i]->m_vAutori[j]->m_sIme <<  vKnjiga[i]->m_vAutori[j]->m_sPrezime<<endl;
			}
		}
	}

}
Knjiga* Main_Knjiznica::PronadjiKnjiguPoOibu(double oib)
{
	Knjiga* oKnjiga = nullptr;
	for (int i = 0; i < vKnjiga.size(); i++)
	{
		if (vKnjiga[i]->m_nsifra == oib)
		{
			oKnjiga = vKnjiga[i];
		}
	}
	return oKnjiga;
}
Citatelj* Main_Knjiznica::PronadjiCitateljaPoOibu(int oib)
{
	Citatelj* oCitatelj = nullptr;
	for (int i = 0; i < vCitatelj.size(); i++)
	{
		if (vCitatelj[i]->m_nOib == oib)
		{
			oCitatelj = vCitatelj[i];
		}
	}
	return oCitatelj;
}
Autor* Main_Knjiznica::PronadjiAutoraPoSifri(int sifra)
{
	for (int i = 0; i < vAutor.size(); i++) {
		if (vAutor[i]->m_nSifra==sifra){
			return vAutor[i];
			}
	}
}

void Main_Knjiznica::UnosNoveKnjige() 
{

	int m_nRbr;
	int m_nsifra;
	string m_sNaziv;
	string m_sAutori;
	int m_nGodinaIzdanja;
	string m_sNakladnik;
	vector<Autor*> m_vAutori;
	

	cout << "Unesite sifru knjige: ";
	cin >> m_nsifra;
	cin.ignore();
	Knjiga* knjigaProvjera{};
	for (int i = 0; i < vKnjiga.size(); i++) {
		if (vKnjiga[i]->m_nsifra == m_nsifra) {
			knjigaProvjera = vKnjiga[i];
		}
	}
	if (knjigaProvjera == nullptr) {
		cout << "Unesite naziv knjige: ";
		getline(cin, m_sNaziv);
		cout << "Unesite godinu izdanja: ";
		cin >> m_nGodinaIzdanja;
		cin.ignore();
		cout << "Unesite nakladnika: ";
		getline(cin, m_sNakladnik);
		cout << endl;
		cout << "Odaberite autore knjige" << endl;
		int josAutora = 1;
		bool zarez = true;
		while (josAutora == 1) {
			for (int i = 0; i < vAutor.size(); i++) {
				cout << "Sifra autora: " << vAutor[i]->m_nSifra << "Prezime i ime: " << vAutor[i]->m_sPrezime << " " << vAutor[i]->m_sIme << endl;
			}
			cout << "Unesite sifru autora: ";
			string s;

			cin >> s;
			int sifr = stoi(s);
			m_vAutori.push_back(PronadjiAutoraPoSifri(sifr));

			if (zarez) {
				m_sAutori = s;
				zarez = false;
			}
			else {
				m_sAutori = m_sAutori + "," + s;
			}
			cout << "Ima li knjiga jos autora 1-Da/0-Ne: ";
			cin >> josAutora;
		}
		vKnjiga.push_back(new Knjiga(vKnjiga.size() + 1, m_nsifra, m_sNaziv, m_sAutori, m_nGodinaIzdanja, m_sNakladnik, nullptr, m_vAutori));
		UpisKnjigaXML();
	}
	else {
		cout << "Unjeli ste sifru knjige koja vec postoji" << endl;

	}
}


void Main_Knjiznica::ObrisiXml(int StariId,int oibCitatelja) {
	vector<Knjiga*>::iterator itKnjige;
	for (int i = 0; i < vKnjiga.size(); i++) {
		if (vKnjiga[i]->DajSifru() == StariId) {
			cout << "\nPosudili ste knjigu: " << vKnjiga[i]->DajNaziv() << endl;
			vKnjiga[i]->m_oCitatelj = PronadjiCitateljaPoOibu(oibCitatelja);
			break;
		}
		vKnjiga.clear();
		UcitajXmlKnjige();
	}
	XMLDocument xDoc;
	xDoc.LoadFile("knjige.xml");
	XMLElement* pRoot = xDoc.FirstChildElement("knjigexm")->FirstChildElement("Knjige");
	pRoot->DeleteChildren();
	xDoc.SaveFile("knjige.xml");
	for (itKnjige = vKnjiga.begin(); itKnjige != vKnjiga.end(); ++itKnjige) {
		SpremiCvor(*itKnjige);
	}
}
 

void Main_Knjiznica::PromjeniXml(double oib, int sifra, int sifraAutora) 
{//Ucitavanje XML-a
	XMLDocument xDoc;
	xDoc.LoadFile("knjige.xml");
	XMLElement* pRoot = xDoc.FirstChildElement("knjigexm")->FirstChildElement("Knjige");
	vector<Knjiga*>::iterator itKnjige;

	XMLElement* pElement = pRoot->InsertNewChildElement("Knjiga");



	for (itKnjige = vKnjiga.begin(); itKnjige != vKnjiga.end(); ++itKnjige) {
		if ((*itKnjige)->DajId() == sifra) {

			xDoc.InsertFirstChild(pElement);
			pElement->SetAttribute("r.broj", (*itKnjige)->m_nRbr);
			pElement->SetAttribute("sifra", (*itKnjige)->m_nsifra);
			pElement->SetAttribute("naziv", (*itKnjige)->m_sNaziv.c_str());
			pElement->SetAttribute("autori", (*itKnjige)->m_sAutori.c_str());
			pElement->SetAttribute("godina_izdanja", (*itKnjige)->m_nGodinaIzdanja);
			pElement->SetAttribute("nakladnik", (*itKnjige)->m_sNakladnik.c_str());
			pElement->SetAttribute("oib_citatelja", oib);
		}
		//xDoc
	}
	pRoot->LinkEndChild(pElement);
	xDoc.SaveFile("knjige.xml");
}


void Main_Knjiznica::PosudiKnjigu() {
	DajSveKnjige();
	Knjiga* knjigaZaPosudbu{}; //// Pokazivac na objekte klase Knjiga
	cout << "\nUnesite sifru knjige koju zelite posuditi: ";
	int sifra;
	cin >> sifra;
	int SifraAutora = 0;

	for (int i = 0; i < vKnjiga.size(); i++) {
		if (vKnjiga[i]->m_nsifra == sifra) {
			knjigaZaPosudbu = vKnjiga[i];
			SifraAutora = stoi(vKnjiga[i]->DajAutor());
		}
	}
	if (knjigaZaPosudbu != nullptr) {
		if (knjigaZaPosudbu->m_oCitatelj == nullptr) {
			DajSveCitatelje();
			cout << "\nUnesite oib citatelja koji posuduje knjigu: ";
			int oib;
			cin >> oib;
			Citatelj* citatelj = PronadiCitatelja(oib);
			if (citatelj != nullptr) {
				cout << "\nKnjiga je uspjesno posudena!";
				ObrisiXml(knjigaZaPosudbu->DajSifru(), oib);
			}
			else {
				cout << "Unjeli ste neispravan oib citatelj" << endl;
			}
		}
		else {
			cout << "Knjiga je vec posudenja, nije moguce obaviti akciju" << endl;
		}
	}
	else {
		cout << "Unjeli ste krivu sifru knjige" << endl;
	}
}

void Main_Knjiznica::VratiKnjigu() {
	DajSveKnjige();
	cout << "\nUnesite sifu knjige: ";
	int sifra;
	cin >> sifra;
	Knjiga* knjigaZaVratiti{};
	for (int i = 0; i < vKnjiga.size(); i++) {
		if (vKnjiga[i]->m_nsifra == sifra) {
			knjigaZaVratiti = vKnjiga[i];
		}      		
	}
	if (knjigaZaVratiti != nullptr) {
		if (knjigaZaVratiti->m_oCitatelj == nullptr) {
			cout << "Knjigu nije moguce vratiti/knjiga se nalazi u knjiznici!" << endl;
		}
		else {
			knjigaZaVratiti->m_oCitatelj = nullptr;
			cout << "\nKnjiga je uspjesno vracena!\n" << endl;
		}
	}
	else {
		cout << "Unjeli ste pogresnu sifru knjige" << endl;
	}
	BrisanjePodataka();


}
void Main_Knjiznica::BrisanjePodataka() {
	vector<Knjiga*>::iterator itKnjige;
	XMLDocument xDoc;
	xDoc.LoadFile("knjige.xml");
	XMLElement* pRoot = xDoc.FirstChildElement("knjigexm")->FirstChildElement("Knjige");
	pRoot->DeleteChildren();
	xDoc.SaveFile("knjige.xml");
	for (itKnjige = vKnjiga.begin(); itKnjige != vKnjiga.end(); ++itKnjige) {
		SpremiCvor(*itKnjige);
	}
}
void Main_Knjiznica::ObrisiKnjigu() {
	cout << "\nUnesite sifru knjige: ";
	int sifra;
	cin >> sifra;
	Knjiga* knjiga{};
	for (int i = 0; i < vKnjiga.size(); i++) {
		if (vKnjiga[i]->m_nsifra == sifra) {
			knjiga = vKnjiga[i];
		}
	}
	if (knjiga != nullptr) {
		if (knjiga->m_oCitatelj == nullptr) {
			vector <Knjiga*> vKnjigePomocni;
			for (int i = 0; i < vKnjiga.size(); i++) {
				if (vKnjiga[i]->m_nsifra != sifra) {
					vKnjigePomocni.push_back(vKnjiga[i]);
				}
				else {
					knjiga = vKnjiga[i];
					cout << "\nKnjiga je obrisana!" << endl;
				}
			}
			delete(knjiga);
			vKnjiga = vKnjigePomocni;
			UpisKnjigaXML();
		}
		else {
			cout << "Knjiga je posudenja, nije moguce izvrsiti akciju" << endl;
		}
	}
	else {
		cout << "Unjeli ste krivu sifru knjige!" << endl;
	}
}

void Main_Knjiznica::UpisKnjigaXML() {
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("knjige.xml");
	XMLElement* pRoot = oXmlDocument.FirstChildElement("knjigexm");
	XMLElement* pElement = pRoot->FirstChildElement("Knjige");
	pElement->DeleteChildren();
	oXmlDocument.SaveFile("knjige.xml");
	
	for (int i = 0; i < vKnjiga.size(); i++) {
		SpremiCvor(vKnjiga[i]);
	}
}
void Main_Knjiznica::SpremiCvor(Knjiga* knjiga) {
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("knjige.xml");
	XMLElement* pRoot = oXmlDocument.FirstChildElement("knjigexm");
	XMLElement* pElement = pRoot->FirstChildElement("Knjige");
	XMLElement* pRootElement = oXmlDocument.NewElement("Knjiga");
	oXmlDocument.InsertFirstChild(pRootElement);
	pRootElement->SetAttribute("r.broj", knjiga->m_nRbr);
	pRootElement->SetAttribute("sifra", knjiga->m_nsifra);
	pRootElement->SetAttribute("naziv", knjiga->m_sNaziv.c_str());
	pRootElement->SetAttribute("autori", knjiga->m_sAutori.c_str());
	pRootElement->SetAttribute("godina_izdanja", knjiga->m_nGodinaIzdanja);
	pRootElement->SetAttribute("nakladnik", knjiga->m_sNakladnik.c_str());
	if (knjiga->m_oCitatelj != nullptr) {
		pRootElement->SetAttribute("oib_citatelja", knjiga->m_oCitatelj->m_nOib);
	}
	else {
		pRootElement->SetAttribute("oib_citatelja", 1);
	}
	
	pElement->InsertEndChild(pRootElement);
	oXmlDocument.SaveFile("knjige.xml");
}

Citatelj* Main_Knjiznica::PronadiCitatelja( int m_nOib) {
	bool pronasao = false;
	Citatelj* citatelj{};
	for (int i = 0; i < vCitatelj.size(); i++) {
		if (vCitatelj[i] == nullptr) {
			
			citatelj = nullptr;
		}
		else if (vCitatelj[i] != nullptr) {
			if (vCitatelj[i]->m_nOib == m_nOib) {
				
				citatelj = vCitatelj[i];
				pronasao = true;
			}
		}
	}
	if (pronasao) {
		return citatelj;
	}
	else {
		return nullptr;
	}
}
