#include "console.h"
#include "Agentie_de_Turism.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;

void UI::tipareste(const vector<Agentie_de_Turism>& agentii)
{
	cout << "Agentii de Turism:\n";
	for (const auto& a : agentii)
		cout << a.getDenumire() << '\t' << a.getDestinatie() << '\t' << a.getTip() << '\t' << a.getPret() << '\n';
	cout << "---------------------------\n";
}

void UI::adaugaUI()
{
	string denumire, destinatie, tip;
	int pret;
	cout << "Denumire: ";
	cin >> denumire;
	cout << "Destinatie: ";
	cin >> destinatie;
	cout << "Tip: ";
	cin >> tip;
	cout << "Pret: ";
	cin >> pret;
	srv.addAT(denumire, destinatie, tip, pret);
	cout << "Agentie de turism adaugata cu succes\n";
}

void UI::stergeUI()
{
	string denumire, destinatie;
	cout << "Denumire existenta: ";
	cin >> denumire;
	cout << "Destinatie existenta: ";
	cin >> destinatie;
	srv.deleteAT(denumire, destinatie);
	cout << "Agentie de turism stearsa cu succes!\n";
}

void UI::modifyUI()
{
	string denumire, destinatie, tip; int pret;
	cout << "Denumire existenta: ";
	cin >> denumire;
	cout << "Destinatie existenta: ";
	cin >> destinatie;
	cout << "Tip: ";
	cin >> tip;
	cout << "Pret: ";
	cin >> pret;
	srv.modifyAT(denumire, destinatie, tip, pret);
	cout << "Agentie de turism modificata cu succes!\n";
}

void UI::findUI()
{
	string denumire, destinatie;
	cout << "Denumire: ";
	cin >> denumire;
	cout << "Destinatie: ";
	cin >> destinatie;
	try
	{
		srv.findAT(denumire, destinatie);
		cout << "Oferta cu denumirea: " + denumire + " si destinatia: " + destinatie + " a fost gasita cu succes!\n";
	}
	catch (ATRepoException&)
	{
		cout << "Aceasta oferta nu a fost gasita deoarece nu exista in momentul de fata!\n";
	}
}

void UI::undo()
{
	try
	{
		srv.undo();
		cout << "Undo s-a realizat cu succes!\n";
		tipareste(srv.getAll());
	}
	catch (ATRepoException&)
	{
		cout << "Nu se mai poate realiza undo!\n";
	}
}

void UI::addWishListUI()
{
	string denumire, destinatie;
	cout << "Denumirea agentiei este: ";
	cin >> denumire;
	cout << "Destinatia agentiei este: ";
	cin >> destinatie;
	try
	{
		srv.addATWishListService(denumire, destinatie);
		cout << "Oferta adaugata cu succes in WishList!\n";
	}
	catch (ATRepoException&)
	{
		cout << "Nu s-a putut adauga deoarece nu exista aceasta agentie de turism!\n";
	}
	catch (ValidateException&)
	{
		cout << "Agentia nu este valida!\n";
	}
}

void UI::addRandomUI()
{
	int nr;
	cout << "Numarul de agentii care se vor adauga este: ";
	cin >> nr;
	try
	{
		int nred = srv.addRandomService(nr);
		cout << "S-au adaugat " << nred << " agentii in WishList!\n";
	}
	catch (ATRepoException&)
	{
		cout << "INVALID!";
	}
}

void UI::emptyWishListUI()
{
	srv.emptyWishListService();
	cout << "S-au sters toate agentiile de turism din WishList-ul curent!\n";
}

void UI::WishListUI()
{
	int cmd;
	int run = 1;
	while (run)
	{
		cout << "\nMeniu:\n";
		cout << "\t1. Adauga agentie de turism in WishList\n";
		cout << "\t2. Adauga agentii de turism random in WishList\n";
		cout << "\t3. Goleste WishList\n";
		cout << "\t4. Afiseaza WishList curent\n";
		cout << "\t5. Inapoi la meniul principal\n";
		cout << "\n\tComanda este: ";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			addWishListUI();
			break;
		case 2:
			addRandomUI();
			break;
		case 3:
			emptyWishListUI();
			break;
		case 4:
			tipareste(srv.getAllWishListService());
			break;
		case 5:
			run = 0;
			break;
		default:
			break;
		}
	}
}

void UI::start()
{
	while (true)
	{
		cout << "\nMeniu:\n";
		cout << "1. Adauga\n";
		cout << "2. Sterge\n";
		cout << "3. Modifica\n";
		cout << "4. Cautare oferta\n";
		cout << "5. Filtrare dupa destinatie\n";
		cout << "6. Filtrare dupa pret\n";
		cout << "7. Sortare dupa denumire\n";
		cout << "8. Sortare dupa destinatie\n";
		cout << "9. Sortare dupa tip + pret\n";
		cout << "10. Afisare\n";
		cout << "11. WishList\n";
		cout << "12. Undo\n";
		cout << "0. Iesire\n";
		cout << "\nDati comanda: ";
		int cmd;
		cin >> cmd;
		try
		{
			switch (cmd)
			{
			case 1:
				adaugaUI();
				break;
			case 2:
				stergeUI();
				break;
			case 3:
				modifyUI();
				break;
			case 4:
				findUI();
				break;
			case 5:
				cout << "Dati o litera cu care sa inceapa destiantiile: ";
				char destinatie;
				cin >> destinatie;
				tipareste(srv.filtrareDestinatie(destinatie));
				break;
			case 6:
				cout << "Dati pret maxim:";
				int pret;
				cin >> pret;
				tipareste(srv.filtrarePretMaiMic(pret));
				break;
			case 7:
				tipareste(srv.sortByDenumire());
				break;
			case 8:
				tipareste(srv.sortByDestinatie());
				break;
			case 9:
				tipareste(srv.sortByTipPret());
				break;
			case 10:
				tipareste(srv.getAll());
				break;
			case 11:
				WishListUI();
				break;
			case 12:
				undo();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida!\n";
			}
		}
		catch (const ATRepoException& ex)
		{
			cout << ex << "\n";
		}
		catch (const ValidateException& ex)
		{
			cout << ex << '\n';
		}
	}
}