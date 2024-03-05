#pragma once
#include <string>
#include "Agentie_de_Turism.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException
{
	vector<string> msgs;

public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}

	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};


ostream& operator<<(ostream& out, const ValidateException& ex);


class ATValidator
{
public:
	void validate(const Agentie_de_Turism& a);
};


void TestValidator();