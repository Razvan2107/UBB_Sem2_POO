#pragma once
#include <string>
#include <iostream>

using std::string;

class Agentie_de_Turism
{
	std::string denumire;
	std::string destinatie;
	std::string tip;
	int pret;

public:
	Agentie_de_Turism(const string denumire, const string destinatie, const string tip, int pret) :denumire{ denumire }, destinatie{ destinatie }, tip{ tip }, pret{ pret } {}

	Agentie_de_Turism(const Agentie_de_Turism& o) :denumire{ o.denumire }, destinatie{ o.destinatie }, tip{ o.tip }, pret{ o.pret } { /*std::cout << "COPY CALLED!\n";*/ }

	string getDenumire() const
	{
		return denumire;
	}

	string getDestinatie() const
	{
		return destinatie;
	}

	string getTip() const
	{
		return tip;
	}

	int getPret() const noexcept
	{
		return pret;
	}

	void setDenumire(string value)
	{
		denumire = value;
	}

	void setDestinatie(string value)
	{
		destinatie = value;
	}

	void setTip(string value)
	{
		tip = value;
	}

	void setPret(int value)
	{
		pret = value;
	}
};

struct dto {
	string destinatie;
	Agentie_de_Turism a;
};


/*
Compara dupa denumire
returneaza true daca a1.denumire e mai mic decat a2.denumire
*/
bool cmpDenumire(const Agentie_de_Turism& a1, const Agentie_de_Turism& a2);

/*
Compara dupa destinatie
returneaza true daca a1.destinatie e mai mic decat a2.destinatie
*/
bool cmpDestinatie(const Agentie_de_Turism& a1, const Agentie_de_Turism& a2);

/*
Compara dupa tip si pret
returneaza true daca a1 e mai mic decat a2
*/
bool cmpTip_Pret(const Agentie_de_Turism& a1, const Agentie_de_Turism& a2);

