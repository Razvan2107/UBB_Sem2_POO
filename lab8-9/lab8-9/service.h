#pragma once

#include "Agentie_de_Turism.h"
#include "repo.h"
#include <vector>
#include <string>

#include <functional>
#include "validator.h"

#include "undo.h"

#include "WishList.h"

using std::vector;
using std::function;
using std::unique_ptr;

class ATService
{
	ATRepoAbs& rep;
	ATValidator& val;

	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	WishList current;
public:
	ATService(ATRepoAbs& rep, ATValidator& val) noexcept :rep{ rep }, val{ val } {}

	//nu permitem copierea de obiecte ATService
	ATService(const ATService& ot) = delete;

	//returneaza toate animalele in ordinea in care au fost adaugate
	vector<Agentie_de_Turism> getAll() noexcept
	{
		return rep.getAll();
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

	void undo();

	/*
	Adauga o agentie cu denumire si destinatie in wishlist

	param denumire: denumirea agentiei care se adauga (string)
	param destinatie: destinatia agentiei care se adauga (string)

	post: agentia este adaugata la wishlist
	
	arunca exceptie daca nu exista agentie cu denumirea si destinatia data
	*/
	void addATWishListService(string denumire, string destinatie);

	/*
	Adauga un numar random de agentii in wishlist

	param nr: numarul de agentii care se adauga (int)

	return: numarul de agentii adaugate in wishlist
	post: se aduaga un numar random de melodii in wishlist
	*/
	int addRandomService(int nr);

	/*
	Elimina toate agentiile din wishlist

	post: wishlist-ul nu contine nicio agentie
	*/
	void emptyWishListService();

	//Returneaza un vector cu toate agentiile din wishlist
	const vector<Agentie_de_Turism>& getAllWishListService();
};

void TestService();