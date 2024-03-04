#pragma once

#include "test.h"
#include <string.h>
#include <assert.h>

//my_utils.c
void testUtils()
{
	char str1[101]= "Ana are mere      ";
	trimTrailing(str1);
	assert(strcmp(str1, "Ana are mere")==0);

	char str2[101]= "mere pere";
	trimTrailing(str2);
	assert(strcmp(str2, "mere pere")==0);
}


//service.c
void testAddService()
{
	MyList v = createEmpty();

	int ok1 = addMaterie(&v, "Prajitura", "Panemar", 20);
	assert(ok1 == 1);

	int ok2 = addMaterie(&v, "", "", 30);
	assert(ok2 == 0);

	int ok3 = addMaterie(&v, "Ecler", "Lidl", -30);
	assert(ok3 == 0);

	assert(size(&v) == 1);
	Materie m = get(&v, 0);

	assert(strcmp(m.nume, "Prajitura") == 0);
	assert(strcmp(m.producator, "Panemar") == 0);
	assert(m.cantitate == 20);
	destroy(&v);
}

void testFindService()
{
	MyList v = createEmpty();

	int ok1 = addMaterie(&v, "Prajitura", "Panemar", 20);
	assert(ok1 == 1);

	int ok2 = addMaterie(&v, "Savarina", "La casa", 30);
	assert(ok2 == 1);

	int ok3 = addMaterie(&v, "Ecler", "Lidl", 25);
	assert(ok3 == 1);

	assert(size(&v) == 3);
	int poz = findMaterie(&v, "Prajitura", "Panemar");

	assert(poz == 0);

	destroy(&v);
	assert(size(&v) == 0);
}

void testModifyService()
{
	MyList v = createEmpty();

	int ok1 = addMaterie(&v, "Prajitura", "Panemar", 20);
	assert(ok1 == 1);

	int ok2 = addMaterie(&v, "Savarina", "La casa", 30);
	assert(ok2 == 1);

	int ok3 = addMaterie(&v, "Ecler", "Lidl", 25);
	assert(ok3 == 1);

	assert(size(&v) == 3);
	int succes1 = modifyMaterie(&v, "Savarina", "La casa", 40);
	assert(succes1 == 1);
	int succes2 = modifyMaterie(&v, "Ecler", "Kaufland", 50);
	assert(succes2 == 0);
	destroy(&v);
}

void testDeleteService()
{
	MyList v = createEmpty();

	int ok1 = addMaterie(&v, "Prajitura", "Panemar", 20);
	assert(ok1 == 1);

	int ok2 = addMaterie(&v, "Savarina", "La casa", 30);
	assert(ok2 == 1);

	int ok3 = addMaterie(&v, "Ecler", "Lidl", 25);
	assert(ok3 == 1);

	assert(size(&v) == 3);
	int succes1 = deleteMaterie(&v, "Savarina", "La casa");
	assert(succes1 == 1);
	assert(size(&v) == 2);
	int succes2 = deleteMaterie(&v, "Ecler", "Kaufland");
	assert(succes2 == 0);
	destroy(&v);
	assert(size(&v) == 0);
}

void testFilterNumeService()
{
	MyList v = createEmpty();

	int ok1 = addMaterie(&v, "Prajitura", "Panemar", 20);
	assert(ok1 == 1);

	int ok2 = addMaterie(&v, "Savarina", "La casa", 30);
	assert(ok2 == 1);

	int ok3 = addMaterie(&v, "Ecler", "Lidl", 25);
	assert(ok3 == 1);

	int ok4 = addMaterie(&v, "Pancakes", "Kaufland", 35);
	assert(ok4 == 1);

	assert(size(&v) == 4);

	MyList filteredList = filterMateriiNume(&v, "P");
	assert(size(&filteredList) == 2);
	destroy(&filteredList);

	filteredList = filterMateriiNume(&v, "A");
	assert(size(&filteredList) == 0);
	destroy(&filteredList);

	filteredList = filterMateriiNume(&v, "");
	assert(size(&filteredList) == 4);
	destroy(&filteredList);

	destroy(&v);
}

void testFilterCantitateService()
{
	MyList v = createEmpty();

	int ok1 = addMaterie(&v, "Prajitura", "Panemar", 20);
	assert(ok1 == 1);

	int ok2 = addMaterie(&v, "Savarina", "La casa", 30);
	assert(ok2 == 1);

	int ok3 = addMaterie(&v, "Ecler", "Lidl", 25);
	assert(ok3 == 1);

	int ok4 = addMaterie(&v, "Pancakes", "Kaufland", 35);
	assert(ok4 == 1);

	assert(size(&v) == 4);

	MyList filteredList = filterMateriiCantitate(&v, 28);
	assert(size(&filteredList) == 2);
	destroy(&filteredList);

	filteredList = filterMateriiCantitate(&v, 15);
	assert(size(&filteredList) == 0);
	destroy(&filteredList);

	filteredList = filterMateriiCantitate(&v, -34);
	assert(size(&filteredList) == 4);
	destroy(&filteredList);

	destroy(&v);
}

void testSortNumeService()
{
	MyList v = createEmpty();

	int ok1 = addMaterie(&v, "Prajitura", "Panemar", 20);
	assert(ok1 == 1);

	int ok2 = addMaterie(&v, "Savarina", "La casa", 30);
	assert(ok2 == 1);

	int ok3 = addMaterie(&v, "Ecler", "Lidl", 25);
	assert(ok3 == 1);

	int ok4 = addMaterie(&v, "Pancakes", "Kaufland", 35);
	assert(ok4 == 1);

	assert(size(&v) == 4);

	MyList sortedList=sortMateriiNume(&v);
	assert(get(&sortedList,0).cantitate==25);
	assert(get(&sortedList,1).cantitate==35);
	assert(get(&sortedList,2).cantitate==20);
	assert(get(&sortedList,3).cantitate==30);

	destroy(&sortedList);
	destroy(&v);
}

void testSortCantitateService()
{
	MyList v = createEmpty();

	int ok2 = addMaterie(&v, "Savarina", "La casa", 30);
	assert(ok2 == 1);

	int ok3 = addMaterie(&v, "Ecler", "Lidl", 25);
	assert(ok3 == 1);

	int ok4 = addMaterie(&v, "Pancakes", "Kaufland", 35);
	assert(ok4 == 1);

	int ok1 = addMaterie(&v, "Prajitura", "Panemar", 20);
	assert(ok1 == 1);

	assert(size(&v) == 4);

	MyList sortedList = sortMateriiCantitate(&v);
	assert(get(&sortedList, 0).cantitate == 20);
	assert(get(&sortedList, 1).cantitate == 25);
	assert(get(&sortedList, 2).cantitate == 30);
	assert(get(&sortedList, 3).cantitate == 35);

	destroy(&sortedList);
	destroy(&v);
}


//MyList.c
void testCreateVector()
{
	MyList v = createEmpty();
	assert(size(&v) == 0);
	destroy(&v);
}

void testIterate()
{
	MyList v = createEmpty();
	Materie m1 = createMaterie("Prajitura", "Panemar", 20);
	Materie m2 = createMaterie("Savarina", "La casa", 30);
	Materie m3 = createMaterie("Ecler", "Lidl", 50);

	add(&v, m1);
	add(&v, m2);
	add(&v, m3);

	assert(size(&v) == 3);
	Materie m = get(&v, 0);

	assert(strcmp(m.nume, "Prajitura") == 0);
	assert(strcmp(m.producator, "Panemar") == 0);
	assert(m.cantitate == 20);

	destroy(&v);
	assert(size(&v) == 0);
}

void testCopy()
{
	MyList v1 = createEmpty();
	add(&v1, createMaterie("Prajitura", "Panemar", 20));
	add(&v1, createMaterie("Savarina", "La casa", 30));

	assert(size(&v1) == 2);
	MyList v2 = copyList(&v1);
	assert(size(&v2) == 2);
	Materie m = get(&v2, 0);
	assert(strcmp(m.nume, "Prajitura") == 0);

	destroy(&v1);
	destroy(&v2);
}


//Cofetarie.c
void testCreateDestroy()
{
	Materie m = createMaterie("Prajitura", "Panemar", 20);

	assert(strcmp(m.nume, "Prajitura") == 0);
	assert(strcmp(m.producator, "Panemar") == 0);
	assert(m.cantitate == 20);

	destroyMaterie(&m);
}

void testValideaza()
{
	Materie m1 = createMaterie("", "Panemar", 20);
	assert(valideazaMaterie(m1) == 0);

	Materie m2 = createMaterie("Prajitura", "", 20);
	assert(valideazaMaterie(m2) == 0);

	Materie m3 = createMaterie("Prajitura", "Panemar", -20);
	assert(valideazaMaterie(m3) == 0);

	Materie m4 = createMaterie("Prajitura", "Panemar", 20);
	assert(valideazaMaterie(m4) == 1);

	destroyMaterie(&m1);
	destroyMaterie(&m2);
	destroyMaterie(&m3);
	destroyMaterie(&m4);
}

void testAll()
{
	testUtils();
	testCreateDestroy();
	testValideaza();
	testCreateVector();
	testIterate();
	testCopy();
	testAddService();
	testModifyService();
	testDeleteService();
	testFindService();
	testFilterNumeService();
	testFilterCantitateService();
	testSortNumeService();
	testSortCantitateService();
}

