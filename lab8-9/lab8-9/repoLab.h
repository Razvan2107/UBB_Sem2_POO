#pragma once
#include "Agentie_de_Turism.h"
#include "repoAbstract.h"
#include <vector>
#include <string>
#include <ostream>
#include <map>
#include <random>

using std::vector;
using std::string;
using std::ostream;
using std::map;

class ATRepoLab:public ATRepoAbs
{
	//vector<Agentie_de_Turism> all;

	map<string, Agentie_de_Turism> all;
	float prob;
	/*
	metoda privata daca exista deja a in repository
	*/
	bool exist(const Agentie_de_Turism& a);

	bool ver_prob()
	{
		auto rd = std::default_random_engine(std::random_device{}());
		std::uniform_real_distribution<float> d(0, 1);
		float nr = d(rd);
		return nr < prob;
	}
public:
	ATRepoLab() = default;
	ATRepoLab(float prob_) : prob(prob_) {};
	//nu permitem copierea de obiecte
	ATRepoLab(const ATRepoLab& o) = delete;

	/*
	Salvare Agentie_de_Turism
	arunca exceptie daca mai exista o agentie de turism cu aceeasi denumire si destinatie
	*/
	void store(const Agentie_de_Turism& a);

	/*
	Sterge Agentie_de_Turism
	arunca exceptie daca nu exista o agentie de turism cu aceeasi denumire si destinatie
	*/
	void delete_at(string denumire, string destinatie);

	/*
	Modifica Agentie_de_Turism
	arunca exceptie daca nu exista agentie de turism
	*/
	void modify(string denumire, string destinatie, string tip, int pret);

	/*
	Cauta Agentie_de_Turism
	arunca exceptie daca nu exista agentie de turism
	*/
	Agentie_de_Turism find(string denumire, string destinatie);

	/*
	Returneaza toate animalele salvate
	*/
	vector<Agentie_de_Turism> getAll() const noexcept;

};