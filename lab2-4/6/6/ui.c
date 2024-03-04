#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdbool.h>

#include "my_utils.h"
#include "service.h"
#include "test.h"
//#include "Cofetarie.h"
//#include "MyList.h"


void printAll(MyList* v)
{
	if (v->length == 0)
		printf("Nu exista materii!\n");
	else
	{
		printf("Materiile curente sunt:\n");
		for (int i = 0; i < size(v); i++)
		{
			Materie m = get(v, i);
			printf("Nume: %s | Producator: %s | Cantitate: %d\n", m.nume, m.producator, m.cantitate);
		}
	}
}

void printMenu()
{
	printf("1. Adauga de materie prima\n");
	printf("2. Modificare materie prima\n");
	printf("3. Stergere materie prima\n");
	printf("4. Vizualizare materii prime care satisfac un criteriu: Nume care incepe cu o litera data\n");
	printf("5. Vizualizare materii prime care satisfac un criteriu:	Cantitate disponibila e mai mica decat un numar dat\n");
	printf("6. Vizualizare materii prime din stoc ordonat dupa nume (crescator/descrescator)\n");
	printf("7. Vizualizare materii prime din stoc ordonat dupa cantitatea disponibila (crescator/descrescator)\n");
	printf("8. Afisarea lista curenta de materii\n");
	printf("9. Iesire\n");
}

void uiAdd(MyList* v)
{
	char nume[30], producator[30], temp; int cantitate;
	scanf_s("%c", &temp, 1);
	printf("Numele materiei este:");
	fgets(nume, 30, stdin);
	printf("Producatorul materiei este:");
	fgets(producator, 30, stdin);
	printf("Cantitatea materiei este:");
	scanf_s("%d", &cantitate);
	trimTrailing(nume);
	trimTrailing(producator);

	int ok = addMaterie(v, nume, producator, cantitate);
	if (ok)
		printf("\nMaterie adaugata cu succes!\n");
	else
		printf("\nMaterie invalida!\n");
}

void uiModify(MyList* v)
{
	char nume[30], producator[30], temp; int cantitateNoua;
	scanf_s("%c", &temp, 1);
	printf("Numele materiei este:");
	fgets(nume, 30, stdin);
	printf("Producatorul materiei este:");
	fgets(producator, 30, stdin);
	printf("Noua cantitate este:");
	scanf_s("%d", &cantitateNoua);

	trimTrailing(nume);
	trimTrailing(producator);

	int ok = modifyMaterie(v, nume, producator, cantitateNoua);
	if (ok)
		printf("\nMaterie modificata cu succes!\n");
	else
		printf("\nNu exista materie cu datele date!\n");
}

void uiDelete(MyList* v)
{
	char nume[30], producator[30], temp;
	scanf_s("%c", &temp, 1);
	printf("Numele materiei este:");
	fgets(nume, 30, stdin);
	printf("Producatorul materiei este:");
	fgets(producator, 30, stdin);

	trimTrailing(nume);
	trimTrailing(producator);
	int ok = deleteMaterie(v, nume, producator);
	if (ok)
		printf("\nMaterie stearsa cu succes!\n");
	else
		printf("\nNu exista materie cu datele date!\n");
}

void uiFilter1(MyList* v)
{
	char litera[5], temp;
	scanf_s("%c", &temp, 1);
	printf("Litera care sa fie la inceputul numelui este: ");
	fgets(litera, 5, stdin);
	trimTrailing(litera);
	MyList filteredList = filterMateriiNume(v,litera);
	printAll(&filteredList);
	printf("\nFiltrarea s-a efecutat cu succes!\n");
	destroy(&filteredList);
}

void uiFilter2(MyList* v)
{
	int cantitate;
	printf("Cantitatea maxima dupa care se va face filtrarea este: ");
	scanf_s("%d", &cantitate);
	MyList filteredList = filterMateriiCantitate(v, cantitate);
	printAll(&filteredList);
	printf("\nFiltrarea s-a efectuat cu succes!\n");
	destroy(&filteredList);
}

void uiSort1(MyList* v)
{
	int ok;
	printf("Sortarea va fi (1-crescatoare,0-descrescatoare): ");
	scanf_s("%d", &ok);
	MyList sortedList = sortMateriiNume(v);
	printf("%d", size(&sortedList));
	if (ok == 1)
		printAll(&sortedList);
	else if (ok == 0)
	{
		if (size(&sortedList) == 0)
			printf("Nu exista materii!\n");
		else
		{
			printf("Materiile curente sunt:\n");
			for (int i = size(&sortedList)-1; i >= 0; i--)
			{
				Materie m = get(&sortedList, i);
				printf("Nume: %s | Producator: %s | Cantitate: %d\n", m.nume, m.producator, m.cantitate);
			}
		}
	}
	destroy(&sortedList);
}

void uiSort2(MyList* v)
{
	int ok;
	printf("Sortarea va fi (1-crescatoare,0-descrescatoare): ");
	scanf_s("%d", &ok);
	MyList sortedList = sortMateriiCantitate(v);
	if (ok == 1)
		printAll(&sortedList);
	else if (ok == 0)
	{
		if (size(&sortedList) == 0)
			printf("Nu exista materii!\n");
		else
		{
			printf("Materiile curente sunt:\n");
			for (int i = size(&sortedList) - 1; i >= 0; i--)
			{
				Materie m = get(&sortedList, i);
				printf("Nume: %s | Producator: %s | Cantitate: %d\n", m.nume, m.producator, m.cantitate);
			}
		}
	}
	destroy(&sortedList);
}

void run()
{
	MyList list = createEmpty();
	int run = 1;
	while (run)
	{
		printMenu();
		int cmd;
		printf("\nOptiunea dumneavostra este:");
		scanf_s("%d", &cmd);
		if (cmd == 1)
			uiAdd(&list);
		else if (cmd == 2)
			uiModify(&list);
		else if (cmd == 3)
			uiDelete(&list);
		else if (cmd == 4)
			uiFilter1(&list);
		else if (cmd == 5)
			uiFilter2(&list);
		else if (cmd == 6)
			uiSort1(&list);
		else if (cmd == 7)
			uiSort2(&list);
		else if (cmd == 8)
			printAll(&list);
		else if (cmd == 9)
			destroy(&list),
			run = 0;
		else
			printf("Comanda invalida!\n");
		printf("\n");
	}
}

int main()
{
	testAll();
	run();
	_CrtDumpMemoryLeaks();
}