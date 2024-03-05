#include "Agentie_de_Turism.h"


bool cmpDenumire(const Agentie_de_Turism& a1, const Agentie_de_Turism& a2)
{
	return a1.getDenumire() < a2.getDenumire();
}


bool cmpDestinatie(const Agentie_de_Turism& a1, const Agentie_de_Turism& a2)
{
	return a1.getDestinatie() < a2.getDestinatie();
}

bool cmpTip_Pret(const Agentie_de_Turism& a1, const Agentie_de_Turism& a2)
{
	if (a1.getTip() == a2.getTip())
		return a1.getPret() < a2.getPret();
	return a1.getTip() < a2.getTip();
}