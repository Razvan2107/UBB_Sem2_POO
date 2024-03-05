#pragma once
#include "service.h"
#include "Agentie_de_Turism.h"

class UI
{
	ATService& srv;

	/*
	Citeste datele de la tastatura si adauga Agentie_de_Turism
	arunca exceptie daca: nu se poate salva, nu e valida
	*/
	void adaugaUI();

	/*
	Citeste denumirea si destinatia de la tastatura si sterge Agentie_de_Turism cu aceste date
	arunca exceptie in cazul in care nu exista
	*/
	void stergeUI();

	/*
	Citeste date de la tastatura si modifica Agentie_de_Turism cu aceasta denumire
	arunca exceptie in cazul in care nu exista
	*/
	void modifyUI();

	/*
	Citeste datele de la tastatura si cauta Agentie_de_Turism
	arunca exceptie daca: nu exista aceasta Agentie_de_Turism
	*/
	void findUI();

	/*
	Tipareste o lista de agentii de turism la consola
	*/
	void tipareste(const vector<Agentie_de_Turism>& agentii);

	//Face undo la ultima operatie de adaugare, stergere sau modificare
	void undo();

public:

	UI(ATService& srv) noexcept :srv{ srv } {}

	//nu permitem copierea obiectelor
	UI(const UI& ot) = delete;

	void start();

	void addWishListUI();
	void addRandomUI();
	void emptyWishListUI();
	void WishListUI();
};
