#include "list.h"


void ResizeList(List* l) {
	//Transaction* v = (Transaction*)malloc(sizeof(Transaction) * (l->capacity *= 2));
	//for (int i = 0; i < l->length; ++i)
	//	v[i] = l->v[i];
	//free(l->v);
	//l->v = v;
	if (l->length < l->capacity)
		return;
	ElemType* nElems = malloc(sizeof(ElemType) * (l->capacity + 2));
	for (int i = 0; i < l->length; i++)
		nElems[i] = l->v[i];
	free(l->v);
	l->v = nElems;
	l->capacity += 2;
}

List* CreateList(DestroyFct f) {
	List* l = malloc(sizeof(List));
	l->length = 0;
	l->capacity = 2;
	l->v = malloc(sizeof(Transaction)*l->capacity);
	l->dfnc=f;
	return l;
}

void AddListTransaction(List* l, ElemType e) {
	ResizeList(l);
	l->v[l->length++] = e;
}

void ModifyListTransaction(List* l, int pos, ElemType e) {
	DeleteTransaction(l->v[pos]);
	l->v[pos] = e;
}

void DeleteListTransaction(List* l, int pos) {
	DeleteTransaction(l->v[pos]);
	for (int i = pos; i < l->length; ++i)
		l->v[i] = l->v[i + 1];
	--l->length;
}

Transaction* GetListElement(List* l, int pos) {
	return l->v[pos];
}

int GetListLength(List* l) {
	return l->length;
}


int ValidatePosition(List* l, int pos) {
	return pos >= 0 && pos < l->length;
}

void DeleteList(List* l) {
	for (int i = 0; i < l->length; ++i)
		//DeleteTransaction(&(l->v[i]));
		l->dfnc(l->v[i]);
	free(l->v);
	free(l);
}

List* CopyList(List* l,CopyFct cf) {
	List* r=CreateList(l->dfnc);
	//r.length = l->length;
	//r.capacity = l->capacity;
	//r.v = (Transaction*)malloc(r.capacity * sizeof(Transaction));
	//for (int i = 0; i < r.length; ++i)
	//	r.v[i] = CopyTransaction(&(l->v[i]));
	for (int i = 0; i < GetListLength(l); ++i)
	{
		ElemType p = GetListElement(l, i);
		AddListTransaction(r, cf(p));
	}
	return r;
}

ElemType removeLast(List* l)
{
	ElemType r = l->v[l->length - 1];
	l->length -= 1;
	return r;
}

