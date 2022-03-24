#include <QCoreApplication>
#include "lib/dynamicSoologic/src/icosphere.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IcoSphere sphere = IcoSphere(1.0);
    sphere.runOriginalIco(1.0);
    vertices b= sphere.getOriginalVertices();
    return a.exec();

}
