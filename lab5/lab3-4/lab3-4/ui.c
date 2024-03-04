#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tests.h"

// Helper to add to account
void Add(TransactionStore* l) {
	int day, sum;
	char t, desc[100];
	printf("Enter the transaction day: ");
	(void)scanf("%d", &day);
	printf("Enter the transaction sum: ");
	(void)scanf("%d", &sum);
	printf("Enter the transaction type (I for input or O for output): ");
	(void)scanf("\n%c", &t);
	int type = t == 'I' ? IN : (t == 'O' ? OUT : -1);
	printf("Enter the transaction description: ");
	(void)scanf("%s", desc);
	if (AddTransaction(l, day, sum, type, desc))
		printf("Addition successful\n");
	else
		printf("Addition failed\n");
}

// Helper to modify account
void Modify(TransactionStore* l) {
	int day, sum;
	char t, desc[100];
	printf("Enter the number of the transaction you wish to modify: ");
	int pos;
	(void)scanf("%d", &pos);
	printf("Now enter the new values for the transaction.\n");
	printf("Enter the transaction day: ");
	(void)scanf("%d", &day);
	printf("Enter the transaction sum: ");
	(void)scanf("%d", &sum);
	printf("Enter the transaction type (I for input or O for output): ");
	(void)scanf("\n%c", &t);
	int type = t == 'I' ? IN : (t == 'O' ? OUT : -1);
	printf("Enter the transaction description: ");
	(void)scanf("%s", desc);
	if (ModifyTransaction(l, pos - 1, day, sum, type, desc))
		printf("Modification successful\n");
	else
		printf("Modification failed\n");
}

// Helper to remove from account
void Remove(TransactionStore* l) {
	printf("Enter the transaction you wish to remove: ");
	int pos;
	(void)scanf("%d", &pos);
	if (RemoveTransaction(l, pos - 1))
		printf("Removal successful\n");
	else
		printf("Removal failed\n");
}

// Helper to print all transactions from account
void PrintAccount(TransactionStore* l) {
	int n = CountTransactions(l->allTransactions);
	printf("There are %d transactions in your account:\n", n);
	for (int i = 0; i < n; ++i) {
		Transaction* t = GetTransaction(l, i);
		printf("No %d | Day: %d, Sum: %d, Type: %s, Description: %s\n", i + 1, t->day, t->sum, t->type == IN ? "IN" : t->type == OUT ? "OUT" : "UNKNOWN", t->desc);
	}
	printf("\n");
}

void PrintList(List* l) {
	int n = GetListLength(l);
	printf("There are %d transactions in your account:\n", n);
	for (int i = 0; i < n; ++i) {
		Transaction* t = GetListElement(l, i);
		printf("No %d | Day: %d, Sum: %d, Type: %s, Description: %s\n", i + 1, t->day, t->sum, t->type == IN ? "IN" : t->type == OUT ? "OUT" : "UNKNOWN", t->desc);
	}
	printf("\n");
}

// Helper for filter UI
void FilterAccount(TransactionStore* l) {
	printf("\
1. Only of type input\n\
2. Only of type output\n\
3. Only less than sum\n\
4. Only greater than sum\n\n\
");
	int type, sum = 0;
	(void)scanf("%d", &type);
	--type;
	if (type == LESSSUM || type == GREATERSUM) {
		printf("Enter the sum: ");
		(void)scanf("%d", &sum);
	}
	printf("\n");
	List* t = FilterTransactions(l, type, sum);
	PrintList(t);
	DeleteList(t);
}



void Filter2(TransactionStore* l)
{
	printf("The day after which the filtering will be done:\n");
	int day;
	(void)scanf("%d", &day);
	if (day < 1 || day>31)
		printf("This day is invalid!\n");
	else
	{
		List* r=FilterDay(l, day);
		PrintList(r);
		DeleteList(r);
	}
}


void Verificare(TransactionStore* l)
{
	bool ok = VerificareSoldTotal(l);
	if (ok == true)
		printf("T\n");
	else
		printf("F\n");
}

/// Helper for order UI
void OrderAccount(TransactionStore* l) {
	printf("\
1. Sort by sum in increasing order\n\
2. Sort by sum in decreasing order\n\
3. Sort by day in increasing order\n\
4. Sort by day in decreasing order\n\n\
");
	int type;
	(void)scanf("%d", &type);
	--type;
	List* t = OrderTransactions(l, type);
	PrintList(t);
	DeleteList(t);
}

// Clean up everything
void Exit(TransactionStore* l) {
	DeleteList(l->allTransactions);
	_CrtDumpMemoryLeaks();
	printf("Goodbye");
}

// Main
int main() {
	TestAll();
	TransactionStore l = createTransactionStore();
	AddTransaction(&l, 2, 3, OUT, "Dsadsa");
	AddTransaction(&l, 4, 1, IN, "HAHA");
	AddTransaction(&l, 5, 2, IN, "no");
	printf("Welcome\n");
	PrintAccount(&l);
	while (1) {
		printf("\
0. Exit\n\
1. Add a transaction\n\
2. Modify a transaction\n\
3. Remove a transaction\n\
4. Filter transactions\n\
5. Filter transactions by day\n\
6. Order transactions\n\
7. Undo\n\
8. Verificare sold total\n\n\
");		
		int option;
		(void)scanf("%d", &option);
		switch (option) {
		case 0:
			Exit(&l);
			return 0;
		case 1:
			Add(&l);
			PrintAccount(&l);
			break;
		case 2:
			Modify(&l);
			PrintAccount(&l);
			break;
		case 3:
			Remove(&l);
			PrintAccount(&l);
			break;
		case 4:
			FilterAccount(&l);
			break;
		case 5:
			Filter2(&l);
			break;
		case 6:
			OrderAccount(&l);
			break;
		case 7:
			if (undo(&l))
				printf("No more undo!\n");
			else
				PrintAccount(&l);
			break;
		case 8:
			Verificare(&l);
		}
		printf("\n");
	}
	_CrtDumpMemoryLeaks();
	return 0;
}