#include "repoAbstract.h"
#include "repoLab.h"
#include "repo.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <algorithm>

using std::ostream;
using std::stringstream;
using std::ifstream;
using std::ofstream;




void ATRepoLab::store(const Agentie_de_Turism& a)
{
	if (ver_prob())
		throw ATRepoException("Ghinion!");
	if (exist(a))
		throw ATRepoException("Exista deja aceasta agentie de turism cu denumirea: " + a.getDenumire() + " si destinatia: " + a.getDestinatie());
	this->all[a.getDenumire()] = a;
}

void ATRepoLab::delete_at(string denumire, string destinatie)
{
	if (ver_prob())
		throw ATRepoException("Ghinion!");
	int nr = 0, ok = 0;
	for (const auto& [cheie,a] : all)
	{
		nr++;
		if (a.getDenumire() == denumire && a.getDestinatie() == destinatie)
		{
			ok = 1;
			break;
		}
	}
	if (ok == 0)
		throw ATRepoException("Nu exista aceasta agentie de turism cu denumirea: " + denumire + " si destinatia: " + destinatie);
	else
		//this->all.end()=std::copy(it.begin(), it.end(), this->all.begin());
		this->all.erase(denumire);
}

void ATRepoLab::modify(string denumire, string destinatie, string tip, int pret)
{
	if (ver_prob())
		throw ATRepoException("Ghinion!");
	int ok = 0;
	for (auto& [cheie,a] : all)
		if (a.getDenumire() == denumire)
		{
			a.setDestinatie(destinatie);
			a.setTip(tip);
			a.setPret(pret);
			ok = 1;
		}
	if (ok == 0)
		throw ATRepoException("Nu exista aceasta agnetie de turism cu denumirea: " + denumire);
}


bool ATRepoLab::exist(const Agentie_de_Turism& a)
{
	try
	{
		find(a.getDenumire(), a.getDestinatie());
		return true;
	}
	catch (ATRepoException&)
	{
		return false;
	}
}


Agentie_de_Turism ATRepoLab::find(string denumire, string destinatie) {
	if (all.count(denumire))
		return all[denumire];
	//vector<Agentie_de_Turism>::iterator f = std::find_if(this->all.begin(), this->all.end(), [=](const Agentie_de_Turism& a)
//		{return a.getDenumire() == denumire && a.getDestinatie() == destinatie; });

//	if (f != this->all.end())
//		return (*f);
//	else
		//daca nu exista arunc o exceptie
	throw ATRepoException("Nu exista aceasta agentie de turism cu denumirea: " + denumire + " si destinatia: " + destinatie);
}


vector<Agentie_de_Turism> ATRepoLab::getAll() const noexcept
{
	vector<Agentie_de_Turism> a;
	for (const auto& [cheie, x] : all)
		a.push_back(x);
	return a;
}
