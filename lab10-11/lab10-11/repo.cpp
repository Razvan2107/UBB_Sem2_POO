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


void ATRepo::store(const Agentie_de_Turism& a)
{
	if (exist(a))
		throw ATRepoException("Exista deja aceasta agentie de turism cu denumirea: " + a.getDenumire() + " si destinatia: " + a.getDestinatie());
	this->all.push_back(a);
}

void ATRepo::delete_at(string denumire, string destinatie)
{
	int nr = 0, ok = 0;
	for (const auto& a : all)
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
		this->all.erase(all.begin() + nr - 1);
}

void ATRepo::modify(string denumire, string destinatie, string tip, int pret)
{
	int ok = 0;
	for (auto& a : all)
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
	{
		return false;
	}
}


const Agentie_de_Turism& ATRepo::find(string denumire, string destinatie)
{
	vector<Agentie_de_Turism>::iterator f = std::find_if(this->all.begin(), this->all.end(), [=](const Agentie_de_Turism& a)
		{return a.getDenumire() == denumire && a.getDestinatie() == destinatie; });

	if (f != this->all.end())
		return (*f);
	else
		//daca nu exista arunc o exceptie
		throw ATRepoException("Nu exista aceasta agentie de turism cu denumirea: " + denumire + " si destinatia: " + destinatie);
}


const vector<Agentie_de_Turism>& ATRepo::getAll() const noexcept
{
	return all;
}


ostream& operator<<(ostream& out, const ATRepoException& ex)
{
	out << ex.msg;
	return out;
}


void ATRepoFile::loadFromFile()
{
	ifstream in(this->fileName);
	if (!in.is_open())
		throw ATRepoException("Error open: " + fileName);
	while (!in.eof())
	{
		string denumire;
		in >> denumire;
		if (in.eof())
			break;
		string destinatie, tip;
		in >> destinatie >> tip;
		int pret;
		in >> pret;

		Agentie_de_Turism a{ denumire.c_str(), destinatie.c_str(), tip.c_str(), pret };
		ATRepo::store(a);
	}
	in.close();
}

void ATRepoFile::writeToFile()
{
	ofstream out(this->fileName);
	if (!out.is_open())
		throw ATRepoException("Error open file " + fileName);
	for (auto& a : getAll())
		out << a.getDenumire() << ',' << a.getDestinatie() << ',' << a.getTip() << ',' << a.getPret() << ',';
	out.close();
}


void ATRepoFile::store(const Agentie_de_Turism& a)
{
	ATRepo::store(a);
	writeToFile();
}

void ATRepoFile::delete_at(const Agentie_de_Turism& a)
{
	ATRepo::delete_at(a.getDenumire(), a.getDestinatie());
	writeToFile();
}

void ATRepoFile::modify(const Agentie_de_Turism& a)
{
	ATRepo::modify(a.getDenumire(), a.getDestinatie(), a.getTip(), a.getPret());
	writeToFile();
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
		rep.store(Agentie_de_Turism{ "a","a","i",200 }); assert(false);
	}
	catch (const ATRepoException&)
	{
		assert(true);
	}

	//cauta inexistent
	try
	{
		rep.find("c", "c"); assert(false);
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
		rep.find("a", "b"); assert(false);
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
		rep.delete_at("c", "c"); assert(false);
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
		rep.modify("c", "a", "adc", 204); assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}
}

void TestFileRepo()
{
	ofstream ofs;
	ofs.open("proba.txt", ofstream::out | ofstream::trunc);
	ofs << "a,b,c,123\n";
	ofs << "f,g,h,456\n";
	ofs << "q,w,e,256\n";
	ofs.close();

	try
	{
		ATRepoFile test{ "test2.txt" }; assert(false);
	}
	catch (ATRepoException&)
	{
		assert(true);
	}

	ATRepoFile test{ "proba.txt" };
	assert(test.getAll().size() == 3);

	auto f = test.find("a", "b");
	assert(f.getDenumire() == "a");
	assert(f.getDestinatie() == "b");
	assert(f.getTip() == "c");
	assert(f.getPret() == 123);

	Agentie_de_Turism a{ "asd","zxcv","o",1234 };
	test.store(a);
	assert(test.getAll().size() == 5);

	try
	{
		test.find("asd", "zxcv");
		assert(true);
	}
	catch (ATRepoException&)
	{
		assert(false);
	}
}

void TestRepo()
{
	TestAdaugaRep();
	TestCautaRep();
	TestStergeRep();
	TestModificaRep();
	//TestFileRepo();
}