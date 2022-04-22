#include "icosphere.h"
#include <math.h>

IcoSphere::IcoSphere(float radius)
{
    m_radius = radius;
}

void IcoSphere::runOriginalIco(float radius)
{
    m_radius = radius;
    setOriginalIco();
    //setLatLon(TypeMesh::OriginalIco);
}

void IcoSphere::getNearTriangle(LatLon latlon, const float &radius, TypeMesh _Mesh)
{
    TriangleCartesianas tmp_triangle;
    vertices *tmp;
    if (_Mesh == TypeMesh::OriginalIco)
    {
        tmp = &m_original_ico;
    }
    else if (_Mesh == TypeMesh::Triangles)
    {
        tmp = &m_working;
    }
    else
    {
        return;
    }

    for(auto it = std::begin(tmp->indices); it <= std::end(tmp->indices)-2; it=it+3)
    {
        int indice_point1 = *it;
        int indice_point2 = *(it+1);
        int indice_point3 = *(it+2);
        Cartesianas cart1,cart2,cart3;
        cart1 = GeoMaths::getCartesianasFromIndice(indice_point1, tmp);
        cart2 = GeoMaths::getCartesianasFromIndice(indice_point2, tmp);
        cart3 = GeoMaths::getCartesianasFromIndice(indice_point3, tmp);

        tmp_triangle.p1_coord =cart1;
        tmp_triangle.p2_coord =cart2;
        tmp_triangle.p3_coord =cart3;

        if (GeoMaths::isPointInsideTriangle(tmp_triangle, latlon, m_radius))
        {
            float length = GeoMaths::getEdgeLength(tmp_triangle.p1_coord, tmp_triangle.p2_coord, m_radius);
            if(length< 2 * radius)
            {
                setTriangleAsWorking(tmp_triangle);
                return;
            }
            else
            {
                GeoMaths::divideTriangleInFour(tmp_triangle, m_working, m_radius);
                getNearTriangle(latlon, radius, TypeMesh::Triangles);
            }
        }
    }
    return;
}

bool IcoSphere::isPointInActualTriangle(const LatLon &latlon)
{
    TriangleCartesianas triangle;
    triangle.p1_coord.x = m_working.vertices_cartesianas[0];
    triangle.p1_coord.y = m_working.vertices_cartesianas[1];
    triangle.p1_coord.z = m_working.vertices_cartesianas[2];

    triangle.p2_coord.x = m_working.vertices_cartesianas[3];
    triangle.p2_coord.y = m_working.vertices_cartesianas[4];
    triangle.p2_coord.z = m_working.vertices_cartesianas[5];

    triangle.p3_coord.x = m_working.vertices_cartesianas[6];
    triangle.p3_coord.y = m_working.vertices_cartesianas[7];
    triangle.p3_coord.z = m_working.vertices_cartesianas[8];

    if(GeoMaths::isPointInsideTriangle(triangle,latlon, m_radius))
    {
        return true;
    }
    else
    {
        return false;
    }
}

vertices IcoSphere::getOriginalvertices()
{
    return m_original_ico;
}

vertices IcoSphere::getWorkingvertices()
{
    return m_working;
}

void IcoSphere::setOriginalIco()
{
    float offset_angle = (M_PI/180.0)*18;
    //first point
    m_original_ico.vertices_cartesianas.push_back(0.0);      //x
    m_original_ico.vertices_cartesianas.push_back(0.0);      //y
    m_original_ico.vertices_cartesianas.push_back(m_radius); //z

    for (int i=0;i<5;i++)
    {
        float x = m_radius * cosf(2*M_PI*float(i)/5.0 + offset_angle) * cosf(atanf(0.5));
        float y = m_radius * sinf(2*M_PI*float(i)/5.0 + offset_angle) * cosf(atanf(0.5));
        float z = m_radius * sinf(atanf(0.5));
        m_original_ico.vertices_cartesianas.push_back(x); //x
        m_original_ico.vertices_cartesianas.push_back(y); //y
        m_original_ico.vertices_cartesianas.push_back(z); //z
    }

    for (int i=0;i<5;i++)
    {    
        float x = m_radius * cosf(2*M_PI*float(i)/5.0 - offset_angle) * cosf(atanf(0.5));
        float y = m_radius * sinf(2*M_PI*float(i)/5.0 - offset_angle) * cosf(atanf(0.5));
        float z =-m_radius * sinf(atanf(0.5));

        m_original_ico.vertices_cartesianas.push_back(x); //x
        m_original_ico.vertices_cartesianas.push_back(y); //y
        m_original_ico.vertices_cartesianas.push_back(z); //z
    }

    //last point
    m_original_ico.vertices_cartesianas.push_back(0.0);      //x
    m_original_ico.vertices_cartesianas.push_back(0.0);      //y
    m_original_ico.vertices_cartesianas.push_back(-m_radius); //z


    //indices
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(2);m_original_ico.indices.push_back(1);
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(3);m_original_ico.indices.push_back(2);
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(4);m_original_ico.indices.push_back(3);
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(5);m_original_ico.indices.push_back(4);
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(1);m_original_ico.indices.push_back(5);

    m_original_ico.indices.push_back(1);m_original_ico.indices.push_back(6);m_original_ico.indices.push_back(7);
    m_original_ico.indices.push_back(1);m_original_ico.indices.push_back(7); m_original_ico.indices.push_back(2);
    m_original_ico.indices.push_back(2);m_original_ico.indices.push_back(7); m_original_ico.indices.push_back(8);
    m_original_ico.indices.push_back(2);m_original_ico.indices.push_back(8); m_original_ico.indices.push_back(3);
    m_original_ico.indices.push_back(3);m_original_ico.indices.push_back(8); m_original_ico.indices.push_back(9);
    m_original_ico.indices.push_back(3);m_original_ico.indices.push_back(9); m_original_ico.indices.push_back(4);
    m_original_ico.indices.push_back(4);m_original_ico.indices.push_back(9); m_original_ico.indices.push_back(10);
    m_original_ico.indices.push_back(4);m_original_ico.indices.push_back(10); m_original_ico.indices.push_back(5);
    m_original_ico.indices.push_back(5);m_original_ico.indices.push_back(10) ;m_original_ico.indices.push_back(6);
    m_original_ico.indices.push_back(5);m_original_ico.indices.push_back(6);m_original_ico.indices.push_back(1);

    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(10); m_original_ico.indices.push_back(6);
    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(6); m_original_ico.indices.push_back(7);
    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(7); m_original_ico.indices.push_back(8);
    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(8); m_original_ico.indices.push_back(9);
    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(9);m_original_ico.indices.push_back(10);
}

void IcoSphere::setLatLon(TypeMesh _Mesh)
{
    vertices *tmp;
    if (_Mesh == TypeMesh::OriginalIco)
    {
        tmp = &m_original_ico;
    }
    else if (_Mesh == TypeMesh::Triangles)
    {
        tmp = &m_working;
    }
    else
    {
        tmp = nullptr;
    }
    tmp->vertices_latlon.clear();

    float lat;
    float lon;

    for(auto it = std::begin(tmp->vertices_cartesianas); it <= std::end(tmp->vertices_cartesianas)-2; it=it+3)
    {
        float x = *it;
        float y = *(it+1);
        float z = *(it+2);

        GeoMaths::getLatLonFromCartesiana(lat, lon, x, y, z);
        tmp->vertices_latlon.push_back(lat);
        tmp->vertices_latlon.push_back(lon);
    }
}

void IcoSphere::setCartesiana(TypeMesh _Mesh)
{
    vertices *tmp;
    if (_Mesh == TypeMesh::OriginalIco)
    {
        tmp = &m_original_ico;
    }
    else if (_Mesh == TypeMesh::Triangles)
    {
        tmp = &m_working;
    }
    else
    {
        tmp = nullptr;
    }

    tmp->vertices_cartesianas.clear();
    float x;
    float y;
    float z;

    for(auto it = std::begin(tmp->vertices_latlon); it <= std::end(tmp->vertices_latlon)-1; it=it+2)
    {
        float lat = *it;
        float lon = *(it+1);

        GeoMaths::getCartesianaFromLatLon(m_radius, lat,lon, x, y, z);
        tmp->vertices_cartesianas.push_back(x);
        tmp->vertices_cartesianas.push_back(y);
        tmp->vertices_cartesianas.push_back(z);
    }
}

void IcoSphere::setTriangleAsWorking(const TriangleCartesianas &triangle)
{
    m_working.clear();
    m_working.vertices_cartesianas.push_back(triangle.p1_coord.x);
    m_working.vertices_cartesianas.push_back(triangle.p1_coord.y);
    m_working.vertices_cartesianas.push_back(triangle.p1_coord.z);

    m_working.vertices_cartesianas.push_back(triangle.p2_coord.x);
    m_working.vertices_cartesianas.push_back(triangle.p2_coord.y);
    m_working.vertices_cartesianas.push_back(triangle.p2_coord.z);

    m_working.vertices_cartesianas.push_back(triangle.p3_coord.x);
    m_working.vertices_cartesianas.push_back(triangle.p3_coord.y);
    m_working.vertices_cartesianas.push_back(triangle.p3_coord.z);

    m_working.indices.push_back(0);
    m_working.indices.push_back(1);
    m_working.indices.push_back(2);

}

LatLon IcoSphere::getLatLonFromTriangle(const int &indice, TypeMesh _Mesh)
{
    vertices *tmp_vertices;
    LatLon tmp;
    if (_Mesh == TypeMesh::OriginalIco)
    {
        tmp_vertices = &m_original_ico;
    }
    else if (_Mesh == TypeMesh::Triangles)
    {
        tmp_vertices = &m_working;
    }
    else
    {
        return tmp;
    }

    tmp.lat = tmp_vertices->vertices_latlon[2*indice+0];
    tmp.lon = tmp_vertices->vertices_latlon[2*indice+1];
    return tmp;

}

//int IcoSphere::getIdTriangleContainsPoint(const float &lat, const float &lon, TypeMesh _Mesh)
//{
//    if (_Mesh == TypeMesh::OriginalIco)
//    {
//        m_working = m_original_ico;
//    }

//    for(auto it = std::begin(m_working.indices); it != std::end(m_working.indices)-3; it=it+3)
//    {
//        int indice_point1 = *it;
//        int indice_point2 = *(it+1);
//        int indice_point3 = *(it+2);

//        TriangleLatLon tmp_triangle;

//        tmp_triangle.p1_coord = getLatLonFromTriangle(indice_point1, _Mesh);
//        tmp_triangle.p2_coord = getLatLonFromTriangle(indice_point2, _Mesh);
//        tmp_triangle.p3_coord = getLatLonFromTriangle(indice_point3, _Mesh);

//        LatLon tmp_latlon;
//        tmp_latlon.lat = lat;
//        tmp_latlon.lon = lon;

//        if(GeoMaths::isPointInsideTriangle(tmp_triangle,tmp_latlon))
//        {
//            return *it;
//        }
//    }
//    return -1;

//}

