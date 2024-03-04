#pragma once
#include "MyList.h"
#include <string.h>
#include <stdlib.h>

MyList createEmpty()
{
	MyList v;
	v.capacitate = 2;
	v.length = 0;
	v.elems = malloc(sizeof(ElemType) * v.capacitate);
	return v;
}

void destroy(MyList* v)
{
	for (int i = 0; i < v->length; i++)
	{
		ElemType el = get(v, i);
		destroyMaterie(&el);
	}
	v->length = 0;
	free(v->elems);
}

ElemType get(MyList* v, int poz)
{
	return v->elems[poz];
}

ElemType setElem(MyList* v, int poz, ElemType el)
{
	ElemType replacedElement = v->elems[poz];
	v->elems[poz] = el;
	return replacedElement;
}

int size(MyList* v)
{
	return v->length;
}

void add(MyList* v, ElemType el)
{
	if (v->length == v->capacitate)
	{
		int capacitateNoua = v->capacitate * 2;
		ElemType* aux_elems = malloc(sizeof(ElemType) * capacitateNoua);
		for (int i = 0; i < v->length; i++)
			aux_elems[i] = v->elems[i];
		free(v->elems);
		v->elems = aux_elems;
		v->capacitate = capacitateNoua;
	}
	v->elems[v->length] = el;
	v->length++;
}

ElemType delete(MyList* v, int poz)
{
	ElemType el = v->elems[poz];
	for (int i = poz; i < v->length - 1; i++)		
		v->elems[i] = v->elems[i + 1];
	v->length--;
	return el;
}

MyList copyList(MyList* v)
{
	MyList v_copy = createEmpty();
	for (int i = 0; i < v->length; i++)
	{
		ElemType el = get(v, i);
		add(&v_copy, copyMaterie(el));
	}
	return v_copy;
}


