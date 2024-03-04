#include "validator.h"
#include <assert.h>
#include <sstream>

void ATValidator::validate(const Agentie_de_Turism& a)
{
	vector<string> msgs;
	if (a.getDenumire().size() == 0)
		msgs.push_back("DENUMIRE INVALIDA!");
	if (a.getDestinatie().size() == 0)
		msgs.push_back("DESTINATIE INVALIDA!");
	if (a.getTip().size() == 0)
		msgs.push_back("TIP INVALID!");
	if (a.getPret() < 0)
		msgs.push_back("PRET NEGATIV!");
	if (msgs.size() > 0)
		throw ValidateException(msgs);
}


ostream& operator<<(ostream& out, const ValidateException& ex)
{
	for (const auto& msg : ex.msgs)
		out << msg << " ";
	return out;
}


void TestValidator()
{
	ATValidator v1;
	Agentie_de_Turism a{ "","","",-1 };
	try
	{
		v1.validate(a);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("NEGATIV") >= 0);
		assert(mesaj.find("INVALID") >= 0);
		assert(mesaj.find("INVALIDA") >= 0);
	}
}