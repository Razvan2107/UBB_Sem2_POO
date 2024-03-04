#include "tests.h"
#include <stdbool.h>

void TestDomain() {
	Transaction* t = CreateTransaction(2, 3, IN, "desc");
	assert(t->day == 2 && t->sum == 3 && t->type == IN && !strcmp(t->desc, "desc"));
	assert(ValidateTransaction(2, 3, IN, "desc"));
	assert(!ValidateTransaction(2, -1, OUT, "HAH"));
	assert(!ValidateTransaction(2, 5, 2, "HAH"));
	DeleteTransaction(t);
}

void TestRepo() {
	List* l = CreateList(DeleteTransaction);
	AddListTransaction(l, CreateTransaction(2, 3, OUT, "Dsadsa"));
	AddListTransaction(l, CreateTransaction(4, 1, IN, "HAHA"));
	AddListTransaction(l, CreateTransaction(5, 2, IN, "no"));
	assert(GetListLength(l) == 3);
	assert(ValidatePosition(l, 2));
	assert(!ValidatePosition(l, -1));
	Transaction* t1 = GetListElement(l, 1);
	assert(!strcmp(t1->desc, "HAHA"));
	ModifyListTransaction(l, 1, CreateTransaction(4, 1, IN, "HAHA2"));
	Transaction* t2 = GetListElement(l, 1);
	assert(!strcmp(t2->desc, "HAHA2"));
	DeleteListTransaction(l, 0);
	assert(GetListLength(l) == 2);
	Transaction* t3 = GetListElement(l, 0);
	assert(t3->sum == 1);
	assert(!ValidatePosition(l, 2));
	removeLast(l);
	assert(GetListLength(l) == 1);
	DeleteList(l);
}

void TestService() {
	TransactionStore l = createTransactionStore();
	assert(AddTransaction(&l, 2, 3, OUT, "Dsadsa"));
	assert(AddTransaction(&l, 4, 1, IN, "HAHA"));
	assert(AddTransaction(&l, 5, 2, IN, "no"));
	assert(!AddTransaction(&l, 32, 12, 32, "HA"));

	assert(!strcmp(GetTransaction(&l, 1)->desc, "HAHA"));
	assert(ModifyTransaction(&l, 1, 4, 1, IN, "HAHA2"));
	assert(!ModifyTransaction(&l, 1, -2, 1, IN, "HAHA2"));
	assert(!strcmp(GetTransaction(&l, 1)->desc, "HAHA2"));

	
	List* filter1 = FilterTransactions(&l, LESSSUM, 3);
	assert(CountTransactions(filter1) == 2);
	DeleteList(filter1);
	List* filter2 = FilterTransactions(&l, GREATERSUM, 2);
	assert(CountTransactions(filter2) == 1);
	DeleteList(filter2);
	List* filter3 = FilterTransactions(&l, TYPEIN, 0);
	assert(CountTransactions(filter3) == 2);
	DeleteList(filter3);
	List* filter4 = FilterTransactions(&l, TYPEOUT, 0);
	assert(CountTransactions(filter4) == 1);
	DeleteList(filter4);
	
	List* order1 = OrderTransactions(&l, DECDAY);
	assert(GetListElement(order1, 0)->day == 5);
	DeleteList(order1);
	List* order2 = OrderTransactions(&l, INCDAY);
	assert(GetListElement(order2, 0)->day == 2);
	DeleteList(order2);
	List* order3 = OrderTransactions(&l, DECSUM);
	assert(GetListElement(order3, 0)->sum == 3);
	DeleteList(order3);
	List* order4 = OrderTransactions(&l, INCSUM);
	assert(GetListElement(order4, 0)->sum == 1);
	DeleteList(order4);

	TransactionStore r = createTransactionStore();
	assert(AddTransaction(&r, 2, 3, OUT, "Dsadsa"));
	assert(AddTransaction(&r, 4, 1, IN, "HAHA"));
	List* list = getAllTransactions(&r, "HAH");
	assert(CountTransactions(list) == 1);

	assert(RemoveTransaction(&l, 0));
	assert(!RemoveTransaction(&l, 2));
	assert(GetTransaction(&l, 0)->sum == 1);

	destroyStore(&r);
	destroyStore(&l);
}

int testcomp(const void* a, const void* b) {
	return *((int*)a) - *((int*)b);
}

void TestUtil() {
	int a[] = { 3,2,1,4,6,2 };
	ssort(a, 6, sizeof(int), testcomp);
	assert(a[0] == 1 && a[1] == 2 && a[2] == 2 && a[3] == 3 && a[4] == 4 && a[5] == 6);
}



void testFilter()
{
	TransactionStore l = createTransactionStore();
	assert(AddTransaction(&l, 2, 3, OUT, "Dsadsa"));
	assert(AddTransaction(&l, 4, 1, IN, "HAHA"));
	assert(AddTransaction(&l, 5, 2, IN, "no"));
	assert(!AddTransaction(&l, 32, 12, 32, "HA"));

	List* filter = FilterDay(&l,3);
	assert(CountTransactions(filter) == 2);
	DeleteList(filter);

	destroyStore(&l);
}

void testUndo()
{
	TransactionStore store = createTransactionStore();
	AddTransaction(&store, 12, 1, IN, "ok");
	AddTransaction(&store, 13, 1, IN, "hmm");
	undo(&store);
	List* l = getAllTransactions(&store,NULL);
	assert(GetListLength(l) == 1);
	DeleteList(l);

	undo(&store);
	l = getAllTransactions(&store, NULL);
	assert(GetListLength(l) != 1);
	DeleteList(l);

	assert(undo(&store) != 0);
	assert(undo(&store) != 0);
	assert(undo(&store) != 0);

	destroyStore(&store);
}

void testVerificareSoldTotal()
{
	TransactionStore l = createTransactionStore();
	assert(AddTransaction(&l, 2, 3, OUT, "Dsadsa"));
	assert(AddTransaction(&l, 4, 1, IN, "HAHA"));
	assert(AddTransaction(&l, 5, 2, IN, "no"));

	assert(VerificareSoldTotal(&l) == true);

	TransactionStore r = createTransactionStore();
	assert(AddTransaction(&r, 2, 8, OUT, "Dsadsa"));
	assert(AddTransaction(&r, 4, 1, OUT, "HAHA"));
	assert(AddTransaction(&r, 5, 2, IN, "no"));

	assert(VerificareSoldTotal(&r) == false);
}

void TestAll() {
	TestDomain();
	TestRepo();
	TestService();
	TestUtil();
	testFilter();
	testUndo();
	testVerificareSoldTotal();
}