#include "lab1011.h"
#include <QtWidgets/QApplication>
#include "gui.h"
#include "model_view.h"
//#include "WLgui.h"

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include "console.h"
#include <iostream>
using std::cout;
using std::endl;

void TestAll()
{
    TestValidator();
    cout << "Finished validator tests!" << endl;
    TestRepo();
    cout << "Finished repo tests!" << endl;
    TestService();
    cout << "Finished service tests!" << endl;
}

void aduaga_la_misto(ATService& srv)
{
    srv.addAT("d", "f", "if", 500);
    srv.addAT("b", "g", "ie", 200);
    srv.addAT("a", "h", "in", 400);
    srv.addAT("c", "e", "il", 300);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ATRepo rep;
    ATRepoFile rep{ "at.txt" };
    ATValidator val;
    ATService srv{ rep,val };
    //aduaga_la_misto(srv);
    GUI gui{ srv };
    gui.setWindowState(Qt::WindowMaximized);
    gui.show();
    return a.exec();
}
