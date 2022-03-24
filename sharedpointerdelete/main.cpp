#include <QCoreApplication>
#include <QDebug>
#include <memory>
#include "claseareset.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::shared_ptr<claseareset> instancia = std::make_shared<claseareset>();
    instancia->setuno(4);

    qInfo() << "int antes de reset " << instancia->getuno();
    instancia.reset(new claseareset);


    qDebug() << "int despues de reset " << instancia->getuno();




    return a.exec();
}
