#include "gui.h"

void GUI::initializeGUIComponents()
{
	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	//left part of the window
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//add
	QWidget* form1 = new QWidget;
	QFormLayout* lyForm1 = new QFormLayout;
	form1->setLayout(lyForm1);
	addDenumire = new QLineEdit;
	addDestinatie = new QLineEdit;
	addTip = new QLineEdit;
	addPret = new QLineEdit;
	lyForm1->addRow(aDenumire, addDenumire);
	lyForm1->addRow(aDestinatie, addDestinatie);
	lyForm1->addRow(aTip, addTip);
	lyForm1->addRow(aPret, addPret);
	adaugaAT = new QPushButton("Adauga agentie de turism");
	lyForm1->addWidget(adaugaAT);
	lyLeft->addWidget(form1);

	//delete
	QWidget* form2 = new QWidget;
	QFormLayout* lyForm2 = new QFormLayout;
	form2->setLayout(lyForm2);
	delDenumire = new QLineEdit;
	delDestinatie = new QLineEdit;
	lyForm2->addRow(dDenumire, delDenumire);
	lyForm2->addRow(dDestinatie, delDestinatie);
	stergeAT = new QPushButton("Sterge agentie de turism");
	lyForm2->addWidget(stergeAT);
	lyLeft->addWidget(form2);

	//modify
	QWidget* form3 = new QWidget;
	QFormLayout* lyForm3 = new QFormLayout;
	form3->setLayout(lyForm3);
	modDenumire = new QLineEdit;
	modDestinatie = new QLineEdit;
	modTip = new QLineEdit;
	modPret = new QLineEdit;
	lyForm3->addRow(mDenumire, modDenumire);
	lyForm3->addRow(mDestinatie, modDestinatie);
	lyForm3->addRow(mTip, modTip);
	lyForm3->addRow(mPret, modPret);
	modificaAT = new QPushButton("Modifica agentie de turism");
	lyForm3->addWidget(modificaAT);
	lyLeft->addWidget(form3);

	//sort
	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtDenumire);
	lyRadioBox->addWidget(radioSrtDestinatie);
	lyRadioBox->addWidget(radioSrtTipPret);

	btnSortAT = new QPushButton("Sorteaza agentii de turism");
	lyRadioBox->addWidget(btnSortAT);

	lyLeft->addWidget(groupBox);

	//filter
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterDestinatie = new QLineEdit();
	lyFormFilter->addRow(FilterDestinatie, editFilterDestinatie);
	btnFilterAT = new QPushButton("Filtreaza agentii de turism dupa destinatie");
	lyFormFilter->addWidget(btnFilterAT);

	lyLeft->addWidget(formFilter);

	//WishList
	btnWishList = new QPushButton("WishList");
	lyLeft->addWidget(btnWishList);

	//reload
	btnReloadData = new QPushButton("Refresh");
	lyLeft->addWidget(btnReloadData);

	//right part of the window
	QWidget* right = new QWidget;
	QHBoxLayout* lyRight = new QHBoxLayout;
	right->setLayout(lyRight);

	//table
	int m = 10;
	int n = 4;
	this->tableAT = new QTableView();
	this->tableModel = new MyModel(srv);

	//QStringList HeaderList;
	//HeaderList << "Denumire" << "Destinatie" << "Tip" << "Pret";
	//this->tableAT->setHorizontalHeaderLabels(HeaderList);

	this->tableAT->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableAT->setModel(tableModel);

	lyRight->addWidget(tableAT);

	//undo
	undo = new QPushButton("UNDO");
	lyRight->addWidget(undo);

	din->setLayout(raport);
	lyRight->addWidget(din);

	//final
	lyMain->addWidget(right);
	lyMain->addWidget(left);

	addButtons();
}

void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

void GUI::addButtons()
{
	clearLayout(raport);
	rap = srv.raport();
	for (const auto& [a, b] : rap)
	{
		auto btn = new QPushButton{ QString::fromStdString(a) };
		raport->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [&]()
			{
				QMessageBox::information(nullptr, "Info", QString::number(b));
			});
	}
}

void GUI::reloadATList(vector<Agentie_de_Turism> all)
{	
	emit this->tableModel->layoutChanged();
	this->tableAT->viewport()->update();
	/*
	this->tableAT->clearContents();
	this->tableAT->setRowCount(all.size());

	int n = 0;
	for (auto& a : all)
	{
		this->tableAT->setItem(n, 0, new QTableWidgetItem(QString::fromStdString(a.getDenumire())));
		this->tableAT->setItem(n, 1, new QTableWidgetItem(QString::fromStdString(a.getDestinatie())));
		this->tableAT->setItem(n, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
		this->tableAT->setItem(n, 3, new QTableWidgetItem(QString::number(a.getPret())));
		n++;
	}
	*/
}

void GUI::connectSignalsSlots()
{	
	QObject::connect(adaugaAT, &QPushButton::clicked, this, &GUI::guiAdd);

	QObject::connect(stergeAT, &QPushButton::clicked, this, &GUI::guiDelete);

	QObject::connect(modificaAT, &QPushButton::clicked, this, &GUI::guiModify);

	QObject::connect(btnSortAT, &QPushButton::clicked, [&]()
		{
			if (this->radioSrtDenumire->isChecked())
				this->reloadATList(srv.sortByDenumire());
			else if (this->radioSrtDestinatie->isChecked())
				this->reloadATList(srv.sortByDestinatie());
			else if (this->radioSrtTipPret->isChecked())
				this->reloadATList(srv.sortByTipPret());
		});

	QObject::connect(btnFilterAT, &QPushButton::clicked, [&]()
		{
			string filterD = this->editFilterDestinatie->text().toStdString();
			this->reloadATList(srv.filtrareDestinatie(filterD[0]));
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]()
		{
			this->reloadATList(srv.getAll());
		});

	QObject::connect(undo, &QPushButton::clicked, this, &GUI::guiUndo);

	QObject::connect(btnWishList, &QPushButton::clicked, this, &GUI::guiWishList);
}


void GUI::guiAdd()
{
	try
	{
		string denumire = addDenumire->text().toStdString();
		string destinatie = addDestinatie->text().toStdString();
		string tip = addTip->text().toStdString();
		int pret = addPret->text().toInt();

		addDenumire->clear();
		addDestinatie->clear();
		addTip->clear();
		addPret->clear();

		this->srv.addAT(denumire, destinatie, tip, pret);
		this->addButtons();
		this->reloadATList(this->srv.getAll());

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

void GUI::guiDelete()
{
	try
	{
		string denumire = delDenumire->text().toStdString();
		string destinatie = delDestinatie->text().toStdString();

		delDenumire->clear();
		delDestinatie->clear();

		this->srv.deleteAT(denumire, destinatie);
		this->addButtons();
		this->reloadATList(this->srv.getAll());

		QMessageBox::information(this, "Info", QString::fromStdString("Agentie de turism stearsa cu succes!"));
	}
	catch (ATRepoException&)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se poate sterge aceasta agentie de turism!"));
	}
	catch (ValidateException&)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Agentie de turism invalida!"));
	}
}

void GUI::guiModify()
{
	try
	{
		string denumire = modDenumire->text().toStdString();
		string destinatie = modDestinatie->text().toStdString();
		string tip = modTip->text().toStdString();
		int pret = modPret->text().toInt();

		modDenumire->clear();
		modDestinatie->clear();
		modTip->clear();
		modPret->clear();


		this->srv.modifyAT(denumire, destinatie, tip, pret);
		this->addButtons();
		this->reloadATList(this->srv.getAll());

		QMessageBox::information(this, "Info", QString::fromStdString("Agentie de turism modificata cu succes!"));
	}
	catch (ATRepoException&)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se poate modifica aceasta agentie de turism!"));
	}
	catch (ValidateException&)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Agentie de turism invalida!"));
	}
}

void GUI::guiRaport()
{
	QWidget* window = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
	window->setLayout(layout);

	QTableWidget* t = new QTableWidget{10,2};
	QStringList HeaderList;
	HeaderList << "Destinatie" << "Numar oferte";
	t->setHorizontalHeaderLabels(HeaderList);

	t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	map<string, int> m = srv.raport();

	t->clearContents();
	t->setRowCount(m.size());

	int n = 0;
	for (auto& a : m)
	{
		t->setItem(n, 0, new QTableWidgetItem(QString::fromStdString(a.first)));
		t->setItem(n, 1, new QTableWidgetItem(QString::number(a.second)));
		n++;
	}

	layout->addWidget(t);

	window->show();
}

void GUI::guiUndo()
{
	srv.undo();
	this->addButtons();
	reloadATList(srv.getAll());
}


void GUI::guiWishList()
{
	wl->move(500, 200);
	wl->show();
	wLabel->move(10, 10);
	wLabel->show();
}