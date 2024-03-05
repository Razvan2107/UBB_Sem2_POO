#include "WLgui.h"
#include <qtimer.h>
#include <iostream>

void WishListGUI::initGUIcmps()
{
	//main
	QVBoxLayout* lyMain = new QVBoxLayout{};
	this->setLayout(lyMain);

	//up
	QWidget* left = new QWidget;
	QHBoxLayout* lyLeft = new QHBoxLayout;
	left->setLayout(lyLeft);

	//add
	QWidget* form1 = new QWidget;
	QFormLayout* lyForm1 = new QFormLayout;
	form1->setLayout(lyForm1);
	aDenumire = new QLabel{ "Denumirea agentiei de turism:" };
	aDestinatie = new QLabel{ "Destinatia agentiei de turism:" };
	addDenumire = new QLineEdit;
	addDestinatie = new QLineEdit;
	lyForm1->addRow(aDenumire, addDenumire);
	lyForm1->addRow(aDestinatie, addDestinatie);
	adauga = new QPushButton("Adauga agentie de turism");
	lyForm1->addWidget(adauga);
	lyLeft->addWidget(form1);

	//add random
	QWidget* form2 = new QWidget;
	QFormLayout* lyForm2 = new QFormLayout;
	form2->setLayout(lyForm2);
	Number = new QLabel{ "Numarul de agentii de turism:" };
	addNumber = new QLineEdit;
	lyForm2->addRow(Number, addNumber);
	adaugaRandom = new QPushButton("Adauga agentii random");
	lyForm2->addWidget(adaugaRandom);
	lyLeft->addWidget(form2);

	//empty
	gol = new QPushButton("Goleste WishList");
	lyLeft->addWidget(gol);

	//CRUDGUI
	CRUDGUI = new QPushButton("WishListCRUDGUI");
	lyLeft->addWidget(CRUDGUI);

	//ReadOnlyGUI
	ReadOnlyGUI = new QPushButton("WishListReadOnlyGUI");
	lyLeft->addWidget(ReadOnlyGUI);

	//down
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);


	//list
	this->listAT = new QListWidget;
	lyRight->addWidget(listAT);

	//final
	lyMain->addWidget(right);
	lyMain->addWidget(left);

}

void WishListGUI::reloadTable(const vector<Agentie_de_Turism>& all)
{
	listAT->clear();
	for (const auto& a : all)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.getDenumire()));
		listAT->addItem(item);
	}
}

void WishListGUI::connectSignalSlots()
{
	QObject::connect(adauga, &QPushButton::clicked, this, &WishListGUI::add);

	QObject::connect(adaugaRandom, &QPushButton::clicked, this, &WishListGUI::addRandom);

	QObject::connect(gol, &QPushButton::clicked, this, &WishListGUI::empty);

	QObject::connect(CRUDGUI, &QPushButton::clicked, [&]()
		{
			wTable->move(10, 100);
			wTable->show();
		});

	QObject::connect(ReadOnlyGUI, &QPushButton::clicked, [&]()
		{
			ro->move(10, 300);
			ro->show();
		});
}

void WishListGUI::add()
{
	try
	{
		string denumire = addDenumire->text().toStdString();
		string destinatie = addDestinatie->text().toStdString();
		addDenumire->clear();
		addDestinatie->clear();
		this->wl.addATWishListService(denumire, destinatie);
		this->reloadTable(this->wl.getAllWishListService());
		QMessageBox::information(this, "Info", QString::fromStdString("Agentie de turism adaugata cu succes!"));
	}
	catch (ATRepoException&)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se poate adauaga aceasta agentie de turism!"));
	}
	catch (ValidateException&)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Agentie de turism invalida!"));
	}
}

void WishListGUI::addRandom()
{
	int nr = addNumber->text().toInt();
	addNumber->clear();
	this->wl.addRandomService(nr);
	this->reloadTable(this->wl.getAllWishListService());
}

void WishListGUI::empty()
{
	this->wl.emptyWishListService();
	this->reloadTable(this->wl.getAllWishListService());
}