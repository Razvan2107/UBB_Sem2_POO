#pragma once
#include "Agentie_de_Turism.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class ATRepo
{
	vector<Agentie_de_Turism> all;

	/*
	metoda privata daca exista deja a in repository
	*/
	bool exist(const Agentie_de_Turism& a);

public:
	ATRepo() = default;

	//nu permitem copierea de obiecte
	ATRepo(const ATRepo& o) = delete;

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
	const Agentie_de_Turism& find(string denumire, string destinatie);

	/*
	Returneaza toate animalele salvate
	*/
	const vector<Agentie_de_Turism>& getAll() const noexcept;

};

class ATRepoFile : public ATRepo
{
private:
	string fileName;
	void loadFromFile();
	void writeToFile();
public:
	ATRepoFile(string fName) :ATRepo(), fileName{ fName } {
		loadFromFile();
	};

	void store(const Agentie_de_Turism& a);

	void delete_at(const Agentie_de_Turism& a);

	void modify(const Agentie_de_Turism& a);
};


/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class ATRepoException
{
	string msg;

public:
	ATRepoException(string m) :msg{ m } {};

	//funcite friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ATRepoException& ex);
};


ostream& operator<<(ostream& out, const ATRepoException& ex);


void TestRepo();
