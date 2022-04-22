#ifndef ICOSPHERE_H
#define ICOSPHERE_H
#include <vector>
#include "globalLib/Global/globalLib.h"
#include "geomaths.h"

enum TypeMesh { OriginalIco,
                Triangles };

class DYNAMICSOOLOGIC_EXPORT IcoSphere
{
public:
    IcoSphere(float radius);
    //run
    void runOriginalIco(float radius);

    void getNearTriangle(LatLon latlon, const float &radius, TypeMesh _Mesh);
    bool isPointInActualTriangle(const LatLon &latlon);
    //getter
    vertices getOriginalvertices();
    vertices getWorkingvertices();
private:
    //meth
    void setOriginalIco();
    void setLatLon(TypeMesh);
    void setCartesiana(TypeMesh);
    void setTriangleAsWorking(const TriangleCartesianas &triangle);
    LatLon getLatLonFromTriangle(const int &indice, TypeMesh _Mesh);
//    int getIdTriangleContainsPoint(const float &lat, const float &lon, TypeMesh _Mesh);

    //atr
    vertices m_original_ico;
    vertices m_working;
    float m_radius;
};

#endif // ICOSPHERE_H
