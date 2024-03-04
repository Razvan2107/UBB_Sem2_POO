#include "repo.h"
#include <iostream>
#include <sstream>
#include <assert.h>

using std::ostream;
using std::stringstream;


void ATRepo::store(const Agentie_de_Turism& a)
{
	if (exist(a))
		throw ATRepoException("Exista deja aceasta agentie de turism cu denumirea: " + a.getDenumire() + " si destinatia: " + a.getDestinatie());
	this->all.add(a);
}

void ATRepo::delete_at(string denumire, string destinatie)
{
	int nr = 0,ok=0;
	for (auto a : all)
	{
		nr++;
		if (a.getDenumire() == denumire && a.getDestinatie() == destinatie)
		{
			ok = 1;
			break;
		}
	}
	if(ok==0)
		throw ATRepoException("Nu exista aceasta agentie de turism cu denumirea: " + denumire + " si destinatia: " + destinatie);
	else
		this->all.del(nr);
}

void ATRepo::modify(string denumire, string destinatie, string tip, int pret)
{
	int ok = 0;
	for (auto &a : all)
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


bool ATRepo::exist(const Agentie_de_Turism& a)
{
	try
	{
		find(a.getDenumire(), a.getDestinatie());
		return true;
	}
	catch (ATRepoException&)
	{return false;}
}


const Agentie_de_Turism& ATRepo::find(string denumire, string destinatie)
{
	for (const auto& a : this->all)
		if (a.getDenumire() == denumire && a.getDestinatie() == destinatie)
			return a;

	//daca nu exista arunc o exceptie
	throw ATRepoException("Nu exista aceasta agentie de turism cu denumirea: " + denumire + " si destinatia: " + destinatie);}


const vector<Agentie_de_Turism> ATRepo::getAll()
{
	vector<Agentie_de_Turism> toate;
	for (auto a : this->all)
		toate.push_back(a);
	return toate;
}


ostream& operator<<(ostream& out, const ATRepoException& ex)
{
	out << ex.msg;
	return out;
}



void TestAdaugaRep()
{
	/// Test Store
	ATRepo rep;
	rep.store(Agentie_de_Turism{ "a","a","i",200 });
	assert(rep.getAll().size() == 1);
	assert(rep.find("a", "a").getDenumire() == "a");

	rep.store(Agentie_de_Turism{ "b","b","i",200 });
	assert(rep.getAll().size() == 2);

	//nu pot adauga 2 cu aceeasi denumire si destinatie
	try
	{
		rep.store(Agentie_de_Turism{ "a","a","i",200 });assert(false);
	}
	catch (const ATRepoException&)
	{
		assert(true);
	}

	//cauta inexistent
	try
	{
		rep.find("c", "c");assert(false);
	}
	catch (const ATRepoException& e)
	{
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void TestCautaRep()
{
	ATRepo rep;
	rep.store(Agentie_de_Turism{ "a","a","i",200 });
	rep.store(Agentie_de_Turism{ "b","b","i",200 });

	auto a = rep.find("a", "a");
	assert(a.getDenumire() == "a");
	assert(a.getDestinatie() == "a");

	//arunca exceptie daca nu gaseste
	try
	{
		rep.find("a", "b");assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestStergeRep()
{
	ATRepo rep;
	rep.store(Agentie_de_Turism{ "a","a","i",200 });
	rep.store(Agentie_de_Turism{ "b","b","i",200 });

	rep.delete_at("a", "a");
	assert(rep.getAll().size() == 1);

	try
	{
		rep.delete_at("c", "c");assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestModificaRep()
{
	ATRepo rep;
	rep.store(Agentie_de_Turism{ "a","a","i",200 });
	rep.store(Agentie_de_Turism{ "b","b","i",200 });

	rep.modify("a", "cd", "o", 300);
	auto a = rep.find("a", "cd");
	assert(a.getDenumire() == "a");
	assert(a.getDestinatie() == "cd");
	assert(a.getTip() == "o");
	assert(a.getPret() == 300);

	try
	{
		rep.modify("c", "a", "adc", 204);assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestRepo()
{
	TestAdaugaRep();
	TestCautaRep();
	TestStergeRep();
	TestModificaRep();
}

void testTemplate()
{
	VectorDinamic<int> v;
	v.add(1);
	v.add(2);
	v.add(3);

	int i = 1;
	for (auto x : v)
	{
		assert(i == x);
		i++;
	}
	i = 1;
	IteratorVector<int> it{ v };
	while (it != v.end())
	{
		assert((*it) == i);
		i++, ++it;
	}
	i = 1;
	IteratorVector<int> it2{ v };
	while (it2.valid())
	{
		assert(it2.element() == i);
		i++, it2.next();
	}
}

void testAssignmentOperator()
{
	VectorDinamic<int> v1;
	VectorDinamic<int> v2;

	v1.add(1);
	v1.add(2);

	v2 = v2;
	v2 = v1;
	assert(v2.size() == 2);
}