#pragma once
#include "Observer.h"
#include "WishList.h"
#include <qwidget.h>
#include <qtablewidget.h>
#include <qboxlayout.h>

class WishTabelGui :public QWidget, public Observer
{
	WishList& wl;
	QTableWidget* t = new QTableWidget{ 10,4 };

	void loadTable(const std::vector<Agentie_de_Turism>& all)
	{
		t->clear();
		t->setRowCount(all.size());
		t->setColumnCount(4);
		for (int i = 0; i < all.size(); i++)
		{
			t->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(all[i].getDenumire())));
			t->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(all[i].getDestinatie())));
			t->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(all[i].getTip())));
			t->setItem(i, 3, new QTableWidgetItem(QString::number(all[i].getPret())));
		}
	}

	void initGUI()
	{
		QHBoxLayout* ly = new QHBoxLayout;
		ly->addWidget(t);
		setLayout(ly);
	}

public:
	WishTabelGui(WishList& wl) :wl{ wl } {
		initGUI();
		loadTable(wl.getAllWishList());
		wl.addObserver(this);
		//update();
	}

	void update() override {
		loadTable(wl.getAllWishList());
	}

	~WishTabelGui() {
		wl.removeObserver(this);
	}
};