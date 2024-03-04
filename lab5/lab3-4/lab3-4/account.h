#include "list.h"
#include "util.h"
#include <stdbool.h>


typedef struct {
	List* allTransactions;
	List* undoList;
}TransactionStore;

/// <summary>
/// Adds a transaction
/// </summary>
/// <param name="l">account to add to</param>
/// <param name="day">day of the transaction</param>
/// <param name="sum">transaction sum</param>
/// <param name="type">transaction type</param>
/// <param name="desc">description of transaction</param>
/// <returns>1 if successful, 0 otherwise</returns>
int AddTransaction(TransactionStore* l, int day, int sum, TransactionType type, char* desc);

/// <summary>
/// Modifies a transaction
/// </summary>
/// <param name="l">account to add to</param>
/// <param name="day">day of the transaction</param>
/// <param name="sum">transaction sum</param>
/// <param name="type">transaction type</param>
/// <param name="desc">description of transaction</param>
/// <returns>1 if successful, 0 otherwise</returns>
int ModifyTransaction(TransactionStore* l, int pos, int day, int sum, TransactionType type, char* desc);

/// <summary>
/// Removes a transaction
/// </summary>
/// <param name="l">account to remove from</param>
/// <param name="pos">which transaction to remove</param>
/// <returns>1 if successful, 0 otherwise</returns>
int RemoveTransaction(TransactionStore* l, int pos);

/// <summary>
/// Get a transaction
/// </summary>
/// <param name="l">account</param>
/// <param name="pos">which transaction</param>
/// <returns>pointer to transaction</returns>
Transaction* GetTransaction(TransactionStore* l, int pos);

/// <summary>
/// Counts the number of transactions
/// </summary>
/// <param name="l">account</param>
/// <returns>number of transactions</returns>
int CountTransactions(List* l);

/// <summary>
/// Filter transactions by a type
/// </summary>
/// <param name="l">account</param>
/// <param name="type">Filter Type Enum</param>
/// <param name="sum">parameter for filter if type is 2,3</param>
/// <returns>a new account (copy) with the transactions filtered</returns>
List* FilterTransactions(TransactionStore* l, FilterType type, int sum);

/// <summary>
/// Order transactions
/// </summary>
/// <param name="l">account</param>
/// <param name="type">Order Type Enum</param>
/// <returns>a new account (copy) with the transactions ordered</returns>
List* OrderTransactions(TransactionStore* l, OrderType type);




/*
* Verificarea soldului total a tranzactiilor care au avut loc
* 
* param l: (adresa pentru) transactionstore ul pe care se face operatia
* 
* return: true in cazul in care tranzactiile de tip intrare sunt mai multe sau egale cu cele de tip iesire, false in caz contrar
*/
bool VerificareSoldTotal(TransactionStore* l);

/*
* Filtreaza tranzactiile in functie de ziua in care a avut loc tranzactia, daca s-a efectuat dupa o anumita zi
* 
* param l: (adresa pentru) lista care va fi filtrata (MyList*v)
* param day: ziua dupa care se face filtrarea (int)
* 
* return: lista filtrata in functie de zi
*/
List* FilterDay(TransactionStore* l, int day);

/*
* Returneaza lista anterioara de tranzactii
* 
* return: 0 daca undo-ul este valabil, 1 in cazul in care nu mai este valabil
*/
int undo(TransactionStore* store);

/*
* Creeaza un TransactionStore
* 
*/
TransactionStore createTransactionStore();

/*
* 
*/
List* getAllTransactions(TransactionStore* store, char* typeSubstring);

/*
*/
void destroyStore(TransactionStore* store);