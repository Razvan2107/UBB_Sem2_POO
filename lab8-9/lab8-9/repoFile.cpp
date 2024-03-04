#include <fstream>
#include "repoFile.h"

void ATRepoFile::loadFromFile()
{
	std::ifstream in(fileName);
	if (!in.is_open())
		throw ATRepoException("Error open: " + fileName);
	while (!in.eof())
	{
		std::string denumire;
		in >> denumire;
		if (in.eof())
			break;
		std::string destinatie, tip;
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
	std::ofstream out(fileName);
	if (!out.is_open())
		throw ATRepoException("Error open file " + fileName);
	for (auto& a : getAll())
		out << a.getDenumire() << '\t' << a.getDestinatie() << '\t' << a.getTip() << '\t' << a.getPret() << std::endl;
	out.close();
}


void ATRepoFile:: adauga(const Agentie_de_Turism& a)
{
	ATRepo::store(a);
	writeToFile();
}

void ATRepoFile::sterge(const Agentie_de_Turism& a)
{
	ATRepo::delete_at(a.getDenumire(), a.getDestinatie());
	writeToFile();
}

