// PIN_Knjiznica_VSMTI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Autor.h"
#include "Citatelj.h"
#include "knjiga.h"
#include "Osoba.h"
#include "tinyxml2.h"
#include <vector>
#include "Main_Knjiznica.h"

using namespace std;
using namespace tinyxml2;

int main()
{
	while (true) {
		Main_Knjiznica* knjiznica = new Main_Knjiznica();

		cout << "\n[------------I Z B O R N I K------------]" << endl;
		cout << "1. Popis autora" << endl;
		cout << "2. Popis citatelja" << endl;
		cout << "3. Lista knjiga" << endl;
		cout << "4. Dodavanje knjige" << endl;
		cout << "5. Izdavanje knjige" << endl;
		cout << "6. Brisanje knjige" << endl;
		cout << "7. Vrati knjigu" << endl;
		cout << "8. Izlaz" << endl;
		cout << "\nVas izbor:";
		int izbornik;
		cin >> izbornik;
		switch (izbornik)
		{

		case 1:
			knjiznica->DajAutore();
			break;
		case 2:
			knjiznica->DajSveCitatelje();
			break;
		case 3:
			knjiznica->DajSveKnjige();
			break;
		case 4:
			knjiznica->UnosNoveKnjige();
			break;
		case 5:
			knjiznica->PosudiKnjigu();
			break;
		case 6:
			knjiznica->ObrisiKnjigu();
			break;
		case 7:
			knjiznica->VratiKnjigu();
			break;
		case 8:
			return 0;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
