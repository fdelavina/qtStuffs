#ifndef GEOMATHS_H
#define GEOMATHS_H

#include <vector>
#include "globalLib/Global/globalLib.h"

struct DYNAMICSOOLOGIC_EXPORT LatLon
{
    float lat;
    float lon;
};

struct DYNAMICSOOLOGIC_EXPORT Cartesianas
{
    float x;
    float y;
    float z;
};

struct DYNAMICSOOLOGIC_EXPORT triangleIndices
{
    int indice_1;
    int indice_2;
    int indice_3;
};

struct DYNAMICSOOLOGIC_EXPORT TriangleCartesianas
{
    Cartesianas p1_coord;
    Cartesianas p2_coord;
    Cartesianas p3_coord;
};

struct DYNAMICSOOLOGIC_EXPORT vertices
{
    std::vector<float> vertices_cartesianas; // x,y,z
    std::vector<float> vertices_latlon;      // lat, lon
    std::vector<int> indices;                // p1,p2,p3

    void clear()
    {
        vertices_cartesianas.clear();
        vertices_latlon.clear();
        indices.clear();
    }
};

class DYNAMICSOOLOGIC_EXPORT GeoMaths
{
public:
    GeoMaths() = delete;

    static void getLatLonFromCartesiana(float &lat, float &lon, const float &x, const float &y, const float &z);
    static void getCartesianaFromLatLon(const float &radius, const float &lat, const float &lon, float &x, float &y, float &z);
    static bool isPointInsideTriangle(const TriangleCartesianas &triangle_lat_lon, const LatLon &lat_lon_point,const float radius);
    static Cartesianas getCartesianasFromIndice( int indice, vertices *vertice);
    static void divideTriangleInFour(const TriangleCartesianas &origin_triangle, vertices &new_vertices, const float &radius);
    static Cartesianas getMiddleLatLonBetween(Cartesianas cart_point1, Cartesianas cart_point2);
    static float getEdgeLength(const Cartesianas &p1, const Cartesianas &p2, const float &radius);
    static void getProjectionToTriangle(TriangleCartesianas triangle_cart, Cartesianas point, Cartesianas &projection_point);
    static void productVectorial(const float *u, const float *v, float*result);
    static float productScalar(const float *u, const float *v);
    static float distanceBetween(const Cartesianas &point,const Cartesianas &projection_point);
    static void projectPointToSphere(Cartesianas &point, const float &radius);
};

#endif // GEOMATHS_H
