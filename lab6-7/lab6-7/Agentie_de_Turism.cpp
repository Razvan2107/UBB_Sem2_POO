#include "Agentie_de_Turism.h"


bool cmpDenumire(const Agentie_de_Turism& a1, const Agentie_de_Turism& a2)
{
	return a1.getDenumire() < a2.getDenumire();
}


bool cmpDestinatie(const Agentie_de_Turism& a1, const Agentie_de_Turism& a2)
{
	return a1.getDestinatie() < a2.getDestinatie();
}