#include "FransiLog/FLog2/flogsingleton.h"
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyLoggerSingleton::Instance().WriteLine("Hola que pasa " );

    return a.exec();
}
