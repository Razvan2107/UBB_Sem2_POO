#pragma once
#include <string>
#include "crud.h"
#include "readonly.h"
#include <QWidget.h>
#include "service.h"
#include "Observer.h"
#include <QListWidget.h>
#include <QLayout.h>
#include <QFormLayout>
#include <QLineEdit>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qheaderview.h>
#include <qmessagebox.h>
#include <QRadioButton>
#include <QMessageBox>
#include <qtablewidget.h>

class WishListGUI :public QWidget, public Observer
{
private:
	ATService& wl;
	void initGUIcmps();
	void connectSignalSlots();
	void reloadTable(const vector<Agentie_de_Turism>& all);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	QListWidget* atWidget = new QListWidget;

	QLabel* aDenumire;
	QLabel* aDestinatie;
	QLineEdit* addDenumire;
	QLineEdit* addDestinatie;
	QLineEdit* addNumber;

	QLabel* Number;

	QPushButton* adauga;
	QPushButton* adaugaRandom;
	QPushButton* gol;
	QPushButton* CRUDGUI;
	QPushButton* ReadOnlyGUI;

	QListWidget* listAT;
	WishTabelGui* wTable = new WishTabelGui{ wl.getWishList()};
	ReadOnly* ro = new ReadOnly{ wl.getWishList() };
public:
	WishListGUI(ATService& w) :wl{ w }
	{
		initGUIcmps();
		connectSignalSlots();
		reloadTable(wl.getAllWishListService());
	}

	void add();

	void addRandom();

	void empty();

	void update() override
	{
		reloadTable(wl.getAllWishListService());
	}

	//~WishListGUI()
	//{
	//	wl.removeObserver(this);
	//}
};

class WishLabelGUI :public QLabel, public Observer
{
	WishList& list;
public:
	WishLabelGUI(WishList& wl) :list{ wl } {
		setFont(QFont{ "arial",24 });
		setAttribute(Qt::WA_DeleteOnClose);
		wl.addObserver(this);
		update();
	}

	void update() override
	{
		setText("WishList contine:" + QString::number(list.getAllWishList().size()));
	}
	~WishLabelGUI()
	{
		list.removeObserver(this);
	}
};