#pragma once
#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int addMaterie(MyList* v, char* nume, char* producator, int cantitate)
{
	Materie m = createMaterie(nume, producator, cantitate);
	int ok = valideazaMaterie(m);
	if (!ok)
	{
		destroyMaterie(&m);
		return 0;
	}
	add(v, m);
	return 1;
}

int findMaterie(MyList* v, char* nume, char* producator)
{
	int poz_to_delete = -1;
	for (int i = 0; i < v->length; i++)
	{
		Materie m = get(v, i);
		if (strcmp(m.nume, nume) == 0 && strcmp(m.producator, producator) == 0)
		{
			poz_to_delete = i;
			break;
		}
	}
	return poz_to_delete;
}

int deleteMaterie(MyList* v, char* nume, char* producator)
{
	int poz_to_delete = findMaterie(v, nume, producator);
	if (poz_to_delete != -1)
	{
		Materie m = delete(v, poz_to_delete);
		destroyMaterie(&m);
		return 1;
	}
	return 0;
}

int modifyMaterie(MyList* v, char* nume, char* producator, int cantitate)
{
	int poz_to_delete = findMaterie(v, nume, producator);
	if (poz_to_delete != -1)
	{
		Materie materieNoua = createMaterie(nume, producator, cantitate);
		Materie m = get(v, poz_to_delete);
		destroyMaterie(&m);
		setElem(v, poz_to_delete, materieNoua);
		return 1;
	}
	return 0;
}

MyList filterMateriiNume(MyList* v, char* litera)
{
	if (strcmp(litera,"")!=0){
		MyList filteredList = createEmpty();
		for (int i = 0; i < v->length; i++)
		{
			Materie m = get(v, i);
			if (litera[0] == m.nume[0])
				add(&filteredList, createMaterie(m.nume, m.producator, m.cantitate));
		}
		return filteredList;}
	else return copyList(v);
}

MyList filterMateriiCantitate(MyList*v, int cantitate)
{
	if (cantitate > 0){
		MyList filteredList = createEmpty();
		for (int i = 0; i < v->length; i++)
		{
			Materie m = get(v, i);
			if (cantitate > m.cantitate)
				add(&filteredList, createMaterie(m.nume, m.producator, m.cantitate));
		}
		return filteredList;}
	else return copyList(v);
}

/*
MyList sort(MyList* v, FunctieCompara cmp)
{
	MyList sortedList = copyList(v);
	int ok = 1;
	do {
		ok = 0;
		for (int i = 0; i < size(&sortedList)-1; ++i)
		{
			Materie aux;
			Materie a = get(&sortedList, i);				
			Materie b = get(&sortedList, i+1);
			if (cmp(&a, &b)>0) 
			{
				aux = sortedList.elems[i];
				sortedList.elems[i] = sortedList.elems[i+1];					
				sortedList.elems[i+1] = aux;
				ok = 1;
			}
		}
	} while (ok == 1);
	return sortedList;
}
*/


MyList sort(MyList* v, FunctieCompara cmp)
{
	MyList sortedList = copyList(v);
	for(int i=0;i<size(&sortedList);i++)
		for (int j = i+1; j < size(&sortedList); j++)
		{
			Materie a = get(&sortedList, i);
			Materie b = get(&sortedList, j);
			if (cmp(&a, &b) > 0)
			{
				setElem(&sortedList, i, b);
				setElem(&sortedList, j, a);
			}
		}
	return sortedList;
}



int compare1(const void* p,const void* q)
{
	const Materie* a = p;
	const Materie* b = q;
	return strcmp(a->nume, b->nume);
}

MyList sortMateriiNume(MyList* v)
{
	MyList sortedList = sort(v, compare1);
	return sortedList;
}


int compare2(void* p,void* q)
{
	const Materie* a = p;
	const Materie* b = q;
	return a->cantitate - b->cantitate;
}

MyList sortMateriiCantitate(MyList* v)
{
	MyList sortedList = sort(v, compare2);
	return sortedList;
}


