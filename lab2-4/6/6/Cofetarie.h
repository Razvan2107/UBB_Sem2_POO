#pragma once
#define _CRT_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdbool.h>

typedef struct
{
	char* nume;
	char* producator;
	int cantitate;
}Materie;

/*
* Creeaza o noua materie
*
* param nume: numele materiei (string)
* param producator: producatorul materiei (string)
* param cantitate: cantitatea materiei (int)
* 
* return: materia creata (Materie)
*/
Materie createMaterie(char* nume, char* producator, int cantitate);

/*
* Distruge materie
*/
void destroyMaterie(Materie* m);

/* 
* Valideaza materie
* O materie este valida daca numele si producatorul sunt diferite de "" si cantitatea sa fie un numar strict pozitiv
* param m: materie de validat (Materie)
* 
* return: 1 (daca este valida), 0 (daca nu este valida) (bool)
*/
bool valideazaMaterie(Materie m);

/*
* Creeaza o copie a materiei date
* 
* param m: materie de copiat (Materie)
* 
* return: materia copiata (Materie)
*/
Materie copyMaterie(Materie m);

