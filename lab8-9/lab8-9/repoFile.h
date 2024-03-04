#pragma once
#include "repo.h"

class ATRepoFile: public ATRepo
{
private:
	std::string fileName;
	void loadFromFile();
	void writeToFile();
public:
	ATRepoFile(string fName) :ATRepo(), fileName{ fName } {
		loadFromFile();
	}

	void adauga(const Agentie_de_Turism& a);

	void sterge(const Agentie_de_Turism& a);
};
