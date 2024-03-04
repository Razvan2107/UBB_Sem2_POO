#pragma once
#include "Cofetarie.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

Materie createMaterie(char* nume, char* producator, int cantitate)
{
	Materie m;
	int nr = (int)strlen(nume) + 1;
	m.nume = malloc(nr * sizeof(char));
	strcpy_s(m.nume, nr, nume);

	
	nr = (int)strlen(producator) + 1;
	m.producator = malloc(nr * sizeof(char));
	strcpy_s(m.producator, nr, producator);
	
	m.cantitate = cantitate;
	return m;
}

void destroyMaterie(Materie* m)
{
	free(m->nume);
	free(m->producator);
	m->cantitate = -1;
}

Materie copyMaterie(Materie m)
{
	return createMaterie(m.nume, m.producator, m.cantitate);
}

bool valideazaMaterie(Materie m)
{
	if (strlen(m.nume) == 0)
		return 0;
	if (strlen(m.producator) == 0)
		return 0;
	if (m.cantitate < 1)
		return 0;
	return 1;
}

