//#include <QtGui/QApplication>
#include <QApplication>
//#include <QTranslator>
#include "appl_form.h"
#include <fstream>
#include <unistd.h>
using namespace std;

bool global_flag_after_crash = 0;
//****************************************************************
int main(int argc, char *argv[])
{
    char fname[] = "Greware_working.txt";
    ifstream p(fname);

    if(p){
		global_flag_after_crash = true;
        p.close();
    }else {
        p.close();
        ofstream plik(fname);
        plik << "program started" << endl;
        plik.close();
    }

    QApplication a(argc, argv);
/*
 * 	QTranslator myappTranslator;
	   //myappTranslator.load("myapp_" + QLocale::system().name());

	QLocale lok(QLocale::English);
	   myappTranslator.load(;

	   a.installTranslator(&myappTranslator);
*/

    appl_form w;
    w.show();
    auto rezult = a.exec();
    cout << "Bye" << endl;
    unlink(fname);
    return rezult;
}
