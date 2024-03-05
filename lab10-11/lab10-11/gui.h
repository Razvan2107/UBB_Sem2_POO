#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QListWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "service.h"
#include "WLgui.h"
#include "model_view.h"

using std::vector;
using std::string;
class GUI :public QWidget
{
private:
	ATService& srv;
	
	QPushButton* adaugaAT;
	QLabel* aDenumire = new QLabel{ "Denumirea agentiei de turism:" };
	QLabel* aDestinatie = new QLabel{ "Destinatia agentiei de turism:" };
	QLabel* aTip = new QLabel{ "Tipul agentiei de turism:" };
	QLabel* aPret = new QLabel{ "Pretul agentiei de turism:" };
	QLineEdit* addDenumire;
	QLineEdit* addDestinatie;
	QLineEdit* addTip;
	QLineEdit* addPret;

	QPushButton* stergeAT;
	QLabel* dDenumire = new QLabel{ "Denumirea agentiei de turism:" };
	QLabel* dDestinatie = new QLabel{ "Destinatia agentiei de turism:" };
	QLineEdit* delDenumire;
	QLineEdit* delDestinatie;

	QPushButton* modificaAT;
	QLabel* mDenumire = new QLabel{ "Denumirea agentiei de turism:" };
	QLabel* mDestinatie = new QLabel{ "Destinatia agentiei de turism:" };
	QLabel* mTip = new QLabel{ "Tipul agentiei de turism:" };
	QLabel* mPret = new QLabel{ "Pretul agentiei de turism:" };
	QLineEdit* modDenumire;
	QLineEdit* modDestinatie;
	QLineEdit* modTip;
	QLineEdit* modPret;
	

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSrtDenumire = new QRadioButton(QString::fromStdString("Denumire"));
	QRadioButton* radioSrtDestinatie = new QRadioButton(QString::fromStdString("Destinatie"));
	QRadioButton* radioSrtTipPret = new QRadioButton(QString::fromStdString("Tip+Pret"));
	QPushButton* btnSortAT;

	QLabel* FilterDestinatie = new QLabel{ "Destiantie dupa care se filtreaza:" };
	QLineEdit* editFilterDestinatie;
	QLabel* FilterPret = new QLabel{ "Pret dupa care se filtreaza:" };
	QLineEdit* editFilterPret;
	QPushButton* btnFilterAT;

	QPushButton* btnWishList;

	QPushButton* btnReloadData;

	QTableView* tableAT;
	MyModel* tableModel;
	QListWidget* listAT;

	void initializeGUIComponents();
	void connectSignalsSlots();
	void reloadATList(vector<Agentie_de_Turism> all);

	QVBoxLayout* raport=new QVBoxLayout;
	QWidget* din = new QWidget;

	QPushButton* undo;
	map<string, int> rap;

	WishListGUI* wl = new WishListGUI{ srv };
	WishLabelGUI* wLabel = new WishLabelGUI{ srv.getWishList() };
	WishTabelGui* wTable = new WishTabelGui{ srv.getWishList() };
public:
	GUI(ATService& service) : srv{ service } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadATList(srv.getAll());
	}
	void addButtons();

	void guiAdd();

	void guiDelete();

	void guiModify();

	void guiRaport();

	void guiUndo();

	void guiWishList();
};
