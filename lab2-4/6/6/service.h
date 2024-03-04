#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MyList.h"


/*
* Adauga o materie
* 
* param v: (adrea pentru) lista in care se adauga (MyList*v)
* param nume: numele materiei care se adauga (char*)
* param producator: producatorul materiei care se adauga (char*)
* param cantitate: cantitatea materiei care se adauga (int)
* 
* return: 1 daca materia a fost adaugata cu succes, 0 in cazul contrar (int)
* post: melodia cu datele date este adaugata in lista (daca este o melodie valida)
*/
int addMaterie(MyList* v, char* nume, char* producator, int cantitate);

/*
* Sterge o materie
* 
* param v: (adresa pentru) lista in care se sterge (MyList*v)
* param nume: numele materiei care se sterge (char*)
* param producator: producatorul materiei care se sterge (char*)
* 
* return: 1 daca materia a fost stearsa cu succes, 0 in cazul contrar (int)
* post: materia cu datele date este stearsa din lista (daca este o materie valida)
*/
int deleteMaterie(MyList* v, char* nume, char* producator);

/*
* Modifica o materie
* 
* param v: (adresa pentru) lista in care se modifica (MyList*v)
* param nume: numele materiei care se modifica (char*)
* param producator: producatorul materiei care se modifica (char*)
* param cantitate: noua cantitate a materiei (int)
* 
* return: 1 daca materia a fost modificata cu succes, 0 in cazul contrar (int)
* post: materia cu datele date se va modifica (daca este o materie valida)
*/
int modifyMaterie(MyList* v, char* nume, char* producator, int cantitate);

/*
* Cauta o materie
* 
* param v: (adresa pentru) lista in care se cauta (MyList*v)
* param nume: numele materiei care se cauta (char*)
* param producator: producatorul materiei care se cauta (char*)
* 
* return: pozitia din lista a materiei cautate, -1 daca materia nu exista in lista (int)
*/
int findMaterie(MyList* v, char* nume, char* producator);

/*
* Filtreaza lista de materii in functie de prima litera a numelui acestora
* 
* param v: (adresa pentru) lista care se va filtra (MyList*v)
* param litera: prima litera a numelui dupa care se va face filtrarea
* 
* return: lista filtrata in cazul in care exista astfel de materii, iar lista initiala in cazul in care nu exista astfel de materii (MyList)
*/
MyList filterMateriiNume(MyList* v, char* litera);

/*
* Filtreaza lista de materii in functie daca cantitatea materiei e mai mica decat un numar dat
* 
* param v: (adresa pentru) lista care se va filtra (MyList*v)
* param cantitate: cantitatea dupa care se va face filtrarea
* 
* return: lista filtrata in cazul in care exista astfel de materii, iar lista initiala in cazul in care nu exista astfel de materii (MyList)
*/
MyList filterMateriiCantitate(MyList* v, int cantitate);

typedef int(*FunctieCompara)(void* p, void* q);

/*
* Returneaza o lista sortata dupa un anumit criteriu de comparare
* 
* param v: (adresa pentru) lista data (MyList*v)
* param cmp: criteriul de comparare (FunctieCompara)
* 
* param: o lista sortata dupa un anumit citeriu
*/
MyList sort(MyList* v, FunctieCompara cmp);

/*
* Returneaza o lista sortata crescator de materii
* 
* param v: (adresa pentru) lista data (MyList*v)
* 
* return: o lista sortata de materii dupa numele materiilor (MyList)
*/
MyList sortMateriiNume(MyList* v);

/*
* Returneaza o lista sortata crescator de materii
* 
* param v: (adresa pentru) lista data (MyList*v)
* 
* return: o lista sortata de materii dupa cantiatea materiilor (MyList)
*/
MyList sortMateriiCantitate(MyList* v);

