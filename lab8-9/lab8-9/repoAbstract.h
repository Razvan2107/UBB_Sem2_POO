#pragma once
#include "Agentie_de_Turism.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class ATRepoAbs
{
public:
//TRepoAbs() = default;
	virtual ~ATRepoAbs() = default;
	//nu permitem copierea de obiecte
//TRepoAbs(const ATRepoAbs& o) = delete;

	/*
	Salvare Agentie_de_Turism
	arunca exceptie daca mai exista o agentie de turism cu aceeasi denumire si destinatie
	*/
	virtual void store(const Agentie_de_Turism& a) = 0;

	/*
	Sterge Agentie_de_Turism
	arunca exceptie daca nu exista o agentie de turism cu aceeasi denumire si destinatie
	*/
	virtual void delete_at(string denumire, string destinatie) = 0;

	/*
	Modifica Agentie_de_Turism
	arunca exceptie daca nu exista agentie de turism
	*/
	virtual void modify(string denumire, string destinatie, string tip, int pret) = 0;

	/*
	Cauta Agentie_de_Turism
	arunca exceptie daca nu exista agentie de turism
	*/
	virtual Agentie_de_Turism find(string denumire, string destinatie) = 0;

	/*
	Returneaza toate animalele salvate
	*/
	virtual vector<Agentie_de_Turism> getAll() const noexcept = 0;

};