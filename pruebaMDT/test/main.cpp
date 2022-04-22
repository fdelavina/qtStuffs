#include <QCoreApplication>
#include <QUrl>
#include <QNetworkAccessManager>
#include "lib/dynamicSoologic/src/geomaths.h"
#include "lib/dynamicSoologic/src/icosphere.h"
#include "lib/downloadSoologic/src/manager.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    IcoSphere sphere = IcoSphere(1.0);
//    sphere.runOriginalIco(1.0);
//    vertices b= sphere.getOriginalvertices();

//    LatLon latlon;
//    latlon.lat = 0.0;
//    latlon.lon = 0.0;
//    float radius = 0.2;
//    sphere.getNearTriangle(latlon, radius, TypeMesh::OriginalIco);

    QString imageUrl("http://127.0.0.1:57600/heightmap/21.485863/39.153354/44448/10000/");
    //QString imageUrl("https://file-examples.com/storage/fe02ad24406246a3cc690e0/2017/10/file_example_PNG_500kB.png");
    Manager manage(imageUrl) ;

    return a.exec();

}
