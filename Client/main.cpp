#include "mainwindow.h"
#include <QApplication>
#include "sockabstract.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    sockAbstract sock;
    sock.init();


    return a.exec();
}
