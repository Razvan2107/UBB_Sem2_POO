#include "account.h"
#include <string.h>
#include <stdbool.h>

int AddTransaction(TransactionStore* l, int day, int sum, TransactionType type, char* desc) {
	if (!ValidateTransaction(day, sum, type, desc))
		return 0;
	Transaction* t = CreateTransaction(day, sum, type, desc);
	List* toUndo = CopyList(l->allTransactions, CopyTransaction);
	AddListTransaction(l->allTransactions, t);
	AddListTransaction(l->undoList, toUndo);
	return 1;
}

int ModifyTransaction(TransactionStore* l, int pos, int day, int sum, TransactionType type, char* desc) {
	if (!ValidatePosition(l->allTransactions, pos) || !ValidateTransaction(day, sum, type, desc))
		return 0;
	Transaction* t = CreateTransaction(day, sum, type, desc);
	List* toUndo = CopyList(l->allTransactions, CopyTransaction);
	ModifyListTransaction(l->allTransactions, pos, t);
	AddListTransaction(l->undoList, toUndo);
	return 1;
}

int RemoveTransaction(TransactionStore* l, int pos) {
	if (!ValidatePosition(l->allTransactions, pos))
		return 0;
	List* toUndo = CopyList(l->allTransactions, CopyTransaction);
	DeleteListTransaction(l->allTransactions, pos);
	AddListTransaction(l->undoList, toUndo);
	return 1;
}

Transaction* GetTransaction(TransactionStore* l, int pos) {
	return GetListElement(l->allTransactions, pos);
}

int CountTransactions(List* l) {
	return GetListLength(l);
}

List* FilterTransactions(TransactionStore* l, FilterType type, int sum) {
	List* r = CreateList(DeleteTransaction);
	int n = CountTransactions(l->allTransactions);
	for (int i = 0; i < n; ++i) {
		Transaction* t = GetTransaction(l, i);
		if ((type == TYPEIN && t->type == IN) ||
			(type == TYPEOUT && t->type == OUT) ||
			(type == LESSSUM && t->sum < sum) ||
			(type == GREATERSUM && t->sum > sum))
			AddListTransaction(r, CopyTransaction(t));
	}
	return r;
}

List* OrderTransactions(TransactionStore* l, OrderType type) {
	List* r = CopyList(l->allTransactions, CopyTransaction);
	ssort(r->v, CountTransactions(r), sizeof(Transaction*),
		type == INCSUM ? orderincsum :
		type == DECSUM ? orderdecsum :
		type == INCDAY ? orderincday :
		orderdecday
	);
	return r;
}







List* FilterDay(TransactionStore* l, int day)
{
	List* r = CreateList(DeleteTransaction);
	int n = CountTransactions(l->allTransactions);
	for (int i = 0; i < n; i++)
	{
		Transaction* t = GetTransaction(l, i);
		if (t->day > day)
			AddListTransaction(r, CopyTransaction(t));
	}
	return r;
}

int undo(TransactionStore* store)
{
	if (GetListLength(store->undoList) == 0)
		return 1;
	List* r = removeLast(store->undoList);
	DeleteList(store->allTransactions);
	store->allTransactions = r;
	return 0;
}

TransactionStore createTransactionStore()
{
	TransactionStore r;
	r.allTransactions = CreateList(DeleteTransaction);
	r.undoList = CreateList(DeleteList);
	return r;
}

void destroyStore(TransactionStore* store)
{
	DeleteList(store->allTransactions);
	DeleteList(store->undoList);
}

List* getAllTransactions(TransactionStore* store, char* typeSubstring)
{
	if (typeSubstring == NULL || strlen(typeSubstring) == 0)
		return CopyList(store->allTransactions, CopyTransaction);

	List* r = CreateList(DeleteTransaction);
	for (int i = 0; i < GetListLength(store->allTransactions); i++)
	{
		Transaction* t = GetListElement(store->allTransactions, i);
		if (strstr(t->desc, typeSubstring) != NULL)
			AddListTransaction(r, CopyTransaction(t));
	}
	return r;
}


bool VerificareSoldTotal(TransactionStore* store)
{
	int sum_in = 0, sum_out = 0;
	for (int i = 0; i < GetListLength(store->allTransactions); i++)
	{
		Transaction* t = GetListElement(store->allTransactions, i);
		if (t->type == IN)
			sum_in+=t->sum;
		else
			sum_out+=t->sum;
	}
	if (sum_in - sum_out >= 0)	return true;
	else return false;
}
