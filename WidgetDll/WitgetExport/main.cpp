#include "ventanaprincipal.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaPrincipal w;
//    MainWindow v;
    w.show();
    return a.exec();
}
