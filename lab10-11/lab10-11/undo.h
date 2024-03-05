#pragma once
#include "Agentie_de_Turism.h"
#include "repo.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo
{
	Agentie_de_Turism adaugat;
	ATRepo& rep;
public:
	UndoAdauga(ATRepo& rep, const Agentie_de_Turism& a) :rep{ rep }, adaugat{ a } {}
	void doUndo() override
	{
		rep.delete_at(adaugat.getDenumire(), adaugat.getDestinatie());
	}
};

class UndoSterge :public ActiuneUndo
{
	Agentie_de_Turism sters;
	ATRepo& rep;
public:
	UndoSterge(ATRepo& rep, const Agentie_de_Turism& a) :rep{ rep }, sters{ a } {}
	void doUndo() override
	{
		rep.store(sters);
	}
};

class UndoModifica :public ActiuneUndo
{
	Agentie_de_Turism modificat;
	ATRepo& rep;
public:
	UndoModifica(ATRepo& rep, const Agentie_de_Turism& a) :rep{ rep }, modificat{ a } {}
	void doUndo() override
	{
		rep.modify(modificat.getDenumire(), modificat.getDestinatie(), modificat.getTip(), modificat.getPret());
	}
};