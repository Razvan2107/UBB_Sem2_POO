#include "service.h"
#include <functional>
#include <algorithm>
#include <assert.h>

void ATService::addAT(const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	Agentie_de_Turism a{ denumire,destinatie,tip,pret };
	val.validate(a);
	rep.store(a);
}

void ATService::deleteAT(const string denumire, const string destinatie)
{
	rep.delete_at(denumire, destinatie);
}

void ATService::modifyAT(string denumire, string destinatie, string tip, int pret)
{
	rep.modify(denumire, destinatie, tip, pret);
}

void ATService::findAT(const string& denumire, const string& destinatie)
{
	rep.find(denumire, destinatie);
}

vector<Agentie_de_Turism> ATService::filtreaza(function<bool(const Agentie_de_Turism&)> fct)
{
	vector<Agentie_de_Turism> rez;
	for (const auto& at : rep.getAll())
		if (fct(at))
			rez.push_back(at);
	return rez;
}

vector<Agentie_de_Turism> ATService::filtrareDestinatie(char destinatie)
{
	vector<Agentie_de_Turism> filtered;
	for (const auto& a : rep.getAll())
		if (a.getDestinatie()[0] == destinatie)
			filtered.push_back(a);
	return filtered;
}

vector<Agentie_de_Turism> ATService::filtrarePretMaiMic(int pret) 
{
	return filtreaza([pret](const Agentie_de_Turism& a)noexcept{return a.getPret() <= pret;});
}

vector<Agentie_de_Turism> ATService::generalSort(bool (*criteriu)(const Agentie_de_Turism&, const Agentie_de_Turism&))
{
	vector<Agentie_de_Turism> v{ rep.getAll() };
	for(size_t i=0;i<v.size();i++)
		for(size_t j=i+1;j<v.size();j++)
			if (!criteriu(v[i], v[j]))
			{
				Agentie_de_Turism aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
	return v;
}

vector<Agentie_de_Turism> ATService::sortByDenumire()
{
	return generalSort(cmpDenumire);
}

vector<Agentie_de_Turism> ATService::sortByDestinatie()
{
	return generalSort(cmpDestinatie);
}

vector<Agentie_de_Turism> ATService::sortByTipPret()
{
	return generalSort([](const Agentie_de_Turism& a1, const Agentie_de_Turism& a2)
		{
			if (a1.getTip() == a2.getTip())
				return a1.getPret() < a2.getPret();
			return a1.getTip() < a2.getTip();
		});
}


void TestAdaugaSrv()
{
	ATRepo rep;
	ATValidator val;
	ATService srv{ rep,val };
	srv.addAT("a", "a", "i", 200);
	assert(srv.getAll().size() == 1);

	//adaug ceva invalid
	try
	{
		srv.addAT("", "", "", -200);assert(false);
	}
	catch (ValidateException&)
	{
		assert(true);
	}
}

void TestStergeSrv()
{
	ATRepo rep;
	ATValidator val;
	ATService srv{ rep,val };
	srv.addAT("a", "a", "i", 200);
	srv.addAT("b", "b", "i", 300);

	srv.deleteAT("a", "a");
	assert(srv.getAll().size() == 1);

	try
	{
		srv.deleteAT("c", "c"); assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestModificaSrv()
{
	ATRepo rep;
	ATValidator val;
	ATService srv{ rep,val };
	srv.addAT("a", "a", "i", 200);
	srv.addAT("b", "b", "i", 300);

	srv.modifyAT("a", "cd", "o", 300);
	srv.findAT("a", "cd");

	try
	{
		srv.modifyAT("c", "a", "adc", 204); assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestCautaSrv()
{
	ATRepo rep;
	ATValidator val;
	ATService srv{ rep,val };
	srv.addAT("a", "a", "i", 200);
	srv.addAT("b", "b", "i", 300);
	
	//caut Agentie_de_Turism existenta
	srv.findAT("a", "a");

	//caut Agentie_de_Turism inexistenta
	try
	{
		srv.findAT("c", "c");assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestFiltrareSrv()
{
	ATRepo rep;
	ATValidator val;
	ATService srv{ rep,val };
	srv.addAT("a", "f", "i", 200);
	srv.addAT("b", "h", "i", 300);
	srv.addAT("c", "g", "i", 400);
	srv.addAT("d", "e", "i", 500);
	
	assert(srv.filtrarePretMaiMic(300).size() == 2);
	assert(srv.filtrarePretMaiMic(350).size() == 2);
	assert(srv.filtrarePretMaiMic(600).size() == 4);
	assert(srv.filtrarePretMaiMic(150).size() == 0);

	assert(srv.filtrareDestinatie('f').size() == 1);
	assert(srv.filtrareDestinatie('g').size() == 1);
	assert(srv.filtrareDestinatie('a').size() == 0);
}

void TestSortareSrv()
{
	ATRepo rep;
	ATValidator val;
	ATService srv{ rep,val };
	srv.addAT("d", "f", "ie", 500);
	srv.addAT("a", "h", "ie", 200);
	srv.addAT("c", "g", "ie", 400);
	srv.addAT("b", "e", "if", 300);

	auto a = srv.sortByDenumire()[0];
	assert(a.getDenumire() == "a");

	a = srv.sortByDestinatie()[0];
	assert(a.getDestinatie() == "e");

	a = srv.sortByTipPret()[0];
	assert(a.getPret() == 200);
}

void TestService()
{
	TestAdaugaSrv();
	TestStergeSrv();
	TestModificaSrv();
	TestCautaSrv();
	TestFiltrareSrv();
	TestSortareSrv();
}