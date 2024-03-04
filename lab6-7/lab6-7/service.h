#pragma once

#include "Agentie_de_Turism.h"
#include "repo.h"
#include <vector>
#include <string>

#include <functional>
#include "validator.h"

using std::vector;
using std::function;

class ATService
{
	ATRepo& rep;
	ATValidator& val;

	/*
	Functie generala de filtrare
	fct - poate fi o funcite
	returneaza daor agentiile de turism care trec de filtru (fct(at)==true)
	*/
	vector<Agentie_de_Turism> filtreaza(function<bool(const Agentie_de_Turism&)> fct);

	/*
	Functie de sortare generala
	criteriu - functie care compara 2 Agentie_de_Turism
			 - poate fi orice functie (in afara clasei) care respecta signatura (returneaza bool are 2 paramteri Agentie_de_Turism)
			 - poate fi functie lambda (care nu capteaza nimic in capture list)
	*/
	vector<Agentie_de_Turism> generalSort(bool (*criteriu)(const Agentie_de_Turism&, const Agentie_de_Turism&));
public:
	ATService(ATRepo& rep, ATValidator& val) noexcept :rep{ rep }, val{ val } {}

	//nu permitem copierea de obiecte ATService
	ATService(const ATService& ot) = delete;

	//returneaza toate animalele in ordinea in care au fost adaugate
	const vector<Agentie_de_Turism> getAll()
	{
		return this->rep.getAll();
	}

	/*
	Adauga o noua Agentie_de_Turism
	arunca exceptie daca: nu se poate salva, nu este valida
	*/
	void addAT(const string& denumire, const string& destinatie, const string& tip, const int pret);

	/*
	Sterge o Agentie_de_Turism
	arunca exceptie daca nu exista
	*/
	void deleteAT(const string denumire, const string destinatie);

	/*
	Modifica o Agentie_de_Turism
	*/
	void modifyAT(string denumire, string destinatie, string tip, int pret);

	/*
	Cauta o Agentie_de_Turism
	*/
	void findAT(const string& denumire, const string& destinatie);

	//Filtreaza agentiile de turism dupa destiantie
	//
	//param destinatie: litera cu care sa inceapa agentiile cautate (string)
	//
	//return: lista cu agentiile care respecta acest criteriu
	vector<Agentie_de_Turism> filtrareDestinatie(char destinatie);

	//Filtreaza agentiile de turism cu pret mai mic decat cel dat
	//
	//param pret: pretul maxim a agentiilor cautate (int)
	//
	//return: lista cu agentiile care respecta acest criteriu
	vector<Agentie_de_Turism> filtrarePretMaiMic(int pret);

	//Sorteaza dupa denumire
	vector<Agentie_de_Turism> sortByDenumire();

	//Sorteaza dupa destinatie
	vector<Agentie_de_Turism> sortByDestinatie();

	//Sorteaza dupa tip + pret
	vector<Agentie_de_Turism> sortByTipPret();
};

void TestService();