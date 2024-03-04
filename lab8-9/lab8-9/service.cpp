#include "service.h"
#include <functional>
#include <algorithm>
#include <assert.h>

void ATService::addAT(const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	Agentie_de_Turism a{ denumire,destinatie,tip,pret };
	val.validate(a);
	rep.store(a);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, a)); 
}

void ATService::deleteAT(const string denumire, const string destinatie)
{
	for (auto& a : getAll())
		if (a.getDenumire() == denumire && a.getDestinatie() == destinatie)
			undoActions.push_back(std::make_unique<UndoSterge>(rep, a));
	rep.delete_at(denumire, destinatie);
}

void ATService::modifyAT(string denumire, string destinatie, string tip, int pret)
{
	for(auto& a:getAll())
		if(a.getDenumire()==denumire && a.getDestinatie()==destinatie)
			undoActions.push_back(std::make_unique<UndoModifica>(rep, a));
	rep.modify(denumire, destinatie, tip, pret);
}

void ATService::findAT(const string& denumire, const string& destinatie)
{
	rep.find(denumire, destinatie);
}

vector<Agentie_de_Turism> ATService::filtrareDestinatie(char destinatie)
{
	const vector<Agentie_de_Turism>& allA = getAll();
	vector<Agentie_de_Turism> filter;
	std::copy_if(allA.begin(), allA.end(), back_inserter(filter),
		[destinatie](const Agentie_de_Turism& a)
		{
			return a.getDestinatie()[0] == destinatie;
		});
	return filter;
}

vector<Agentie_de_Turism> ATService::filtrarePretMaiMic(int pret) 
{
	const vector<Agentie_de_Turism>& allA = getAll();
	vector<Agentie_de_Turism> filter;
	std::copy_if(allA.begin(), allA.end(), back_inserter(filter),
		[pret](const Agentie_de_Turism& a)
		{
			return a.getPret() <= pret;
		});
	return filter;
}

vector<Agentie_de_Turism> ATService::sortByDenumire()
{
	vector<Agentie_de_Turism> sorted_list{ rep.getAll() };
	sort(sorted_list.begin(), sorted_list.end(), cmpDenumire);
	return sorted_list;
}

vector<Agentie_de_Turism> ATService::sortByDestinatie()
{
	vector<Agentie_de_Turism> sorted_list{ rep.getAll() };
	sort(sorted_list.begin(), sorted_list.end(), cmpDestinatie);
	return sorted_list;
}

vector<Agentie_de_Turism> ATService::sortByTipPret()
{
	vector<Agentie_de_Turism> sorted_list{ rep.getAll() };
	sort(sorted_list.begin(), sorted_list.end(), cmpTip_Pret);
	return sorted_list;
}


void ATService::undo()
{
	if (undoActions.empty())
		throw ATRepoException{ "Nu mai exista operatii" };
	undoActions.back()->doUndo();
	undoActions.pop_back();
}


void ATService::addATWishListService(string denumire, string destinatie)
{
	const auto& at = rep.find(denumire, destinatie);
	current.addATWishList(at);
}

int ATService::addRandomService(int nr)
{
	current.addRandom(this->getAll(), nr);
	return int(current.getAllWishList().size());
}

void ATService::emptyWishListService()
{
	current.emptyWishList();
}

const vector<Agentie_de_Turism>& ATService::getAllWishListService()
{
	return current.getAllWishList();
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

void TestUndoSrv()
{
	ATRepo rep;
	ATValidator val;
	ATService srv{ rep,val };
	srv.addAT("a", "a", "o", 120);
	srv.addAT("b", "b", "i", 340);
	srv.addAT("c", "c", "i", 420);
	srv.addAT("d", "e", "o", 100);
	
	srv.undo();
	assert(srv.getAll().size() == 3);
	
	srv.deleteAT("b", "b");
	assert(srv.getAll().size() == 2);
	srv.undo();
	assert(srv.getAll().size() == 3);

	srv.modifyAT("a", "a", "ok", 12345);
	srv.undo();

	srv.undo();
	srv.undo();
	srv.undo();
	try
	{
		srv.undo();assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestWishListSrv()
{
	ATRepo rep;
	ATValidator val;
	ATService srv{ rep,val };

	srv.addAT("a", "a", "o", 120);
	srv.addAT("b", "b", "i", 340);
	srv.addAT("c", "c", "i", 420);
	srv.addAT("d", "e", "o", 100);

	srv.addRandomService(2);
	assert(srv.getAllWishListService().size() == 2);
	srv.emptyWishListService();
	assert(srv.getAllWishListService().size() == 0);

	srv.addRandomService(10);
	assert(srv.getAllWishListService().size() == 4);

	srv.emptyWishListService();
	srv.addATWishListService("a", "a");
	assert(srv.getAllWishListService().size() == 1);

	try
	{
		srv.addATWishListService("b", "c");assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestService()
{
	TestAdaugaSrv();
	TestStergeSrv();
	TestModificaSrv();
	TestCautaSrv();
	TestFiltrareSrv();
	TestSortareSrv();
	TestUndoSrv();
	TestWishListSrv();
}