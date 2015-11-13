//#include <QtGui/QApplication>
#include <QApplication>
#include "appl_form.h"


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    appl_form w;
    w.show();
    return a.exec();
}
