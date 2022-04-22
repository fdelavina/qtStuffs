#include "geomaths.h"
#include <math.h>
void GeoMaths::getLatLonFromCartesiana(float &lat, float &lon, const float &x, const float &y, const float &z)
{
    //float radius = sqrtf(powf(x,2) + powf(y,2) + powf(z,2));
    float x_aux;
    abs(x)<=0.0001 ? x_aux = 0.000000001 : x_aux = x;

    lat = atanf(z/x_aux) * 180.0/M_PI;
    lon = atanf(y/x_aux) * 180.0/M_PI;

}

void GeoMaths::getCartesianaFromLatLon(const float &radius, const float &lat, const float &lon, float &x, float &y, float &z)
{
    x = radius * cosf(lat* M_PI/180.0) * cosf(lon* M_PI/180.0);
    y = radius * cosf(lat* M_PI/180.0) * sinf(lon* M_PI/180.0);
    z = radius * sinf(lat* M_PI/180.0);
}

bool GeoMaths::isPointInsideTriangle(const TriangleCartesianas &triangle_cart, const LatLon &lat_lon_point, const float radius)
{
    float n[3];
    float n1[3];
    float n2[3];
    float n3[3];
    Cartesianas projection_point, point;
    getCartesianaFromLatLon(radius, lat_lon_point.lat, lat_lon_point.lon, point.x, point.y, point.z);
    GeoMaths::getProjectionToTriangle(triangle_cart,point, projection_point);
    //algorithm
    if(GeoMaths::distanceBetween(point,projection_point)>=radius)
    {
        return false;
    }
    float p1p [3] = {projection_point.x - triangle_cart.p1_coord.x,
                     projection_point.y - triangle_cart.p1_coord.y,
                     projection_point.z - triangle_cart.p1_coord.z};
    float p2p [3] = {projection_point.x - triangle_cart.p2_coord.x,
                     projection_point.y - triangle_cart.p2_coord.y,
                     projection_point.z - triangle_cart.p2_coord.z};
    float p3p [3] = {projection_point.x - triangle_cart.p3_coord.x,
                     projection_point.y - triangle_cart.p3_coord.y,
                     projection_point.z - triangle_cart.p3_coord.z};

    float p1p2 [3] = {triangle_cart.p2_coord.x - triangle_cart.p1_coord.x,
                      triangle_cart.p2_coord.y - triangle_cart.p1_coord.y,
                      triangle_cart.p2_coord.z - triangle_cart.p1_coord.z};
    float p2p3 [3] = {triangle_cart.p3_coord.x - triangle_cart.p2_coord.x,
                      triangle_cart.p3_coord.y - triangle_cart.p2_coord.y,
                      triangle_cart.p3_coord.z - triangle_cart.p2_coord.z};
    float p3p1 [3] = {triangle_cart.p1_coord.x - triangle_cart.p3_coord.x,
                      triangle_cart.p1_coord.y - triangle_cart.p3_coord.y,
                      triangle_cart.p1_coord.z - triangle_cart.p3_coord.z};

    productVectorial(p1p2,p2p3,n );

    productVectorial(p1p2,p1p,n1 );
    productVectorial(p2p3,p2p,n2 );
    productVectorial(p3p1,p3p,n3 );

    if (productScalar(n,n1) >=0 &&
        productScalar(n,n2) >=0 &&
        productScalar(n,n3) >=0  )
    {
        return true;
    }
    else
    {
        return false;
    }
}

Cartesianas GeoMaths::getCartesianasFromIndice(int indice, vertices *vertices)
{
    Cartesianas tmp;

    tmp.x = vertices->vertices_cartesianas[3*indice + 0 ];
    tmp.y = vertices->vertices_cartesianas[3*indice + 1 ];
    tmp.z = vertices->vertices_cartesianas[3*indice + 2 ];
    return tmp;
}

Cartesianas GeoMaths::getMiddleLatLonBetween(Cartesianas cart_point1, Cartesianas cart_point2)
{
    Cartesianas tmp;

    tmp.x = (cart_point1.x + cart_point2.x)/2.0;
    tmp.y = (cart_point1.y + cart_point2.y)/2.0;
    tmp.z = (cart_point1.z + cart_point2.z)/2.0;
    return tmp;
}

float GeoMaths::getEdgeLength(const Cartesianas &p1, const Cartesianas &p2, const float &radius)
{
    float diff_x = p1.x - p2.x;
    float diff_y = p1.y - p2.y;
    float diff_z = p1.z - p2.z;
    return radius * sqrtf(powf(diff_x,2) + powf(diff_y,2) + powf(diff_z,2));
}

void GeoMaths::getProjectionToTriangle(TriangleCartesianas triangle_cart,
                                       Cartesianas point,
                                       Cartesianas &projection_point )
{
    Cartesianas u,v;

    if(point.x <= 0.000001 && point.x >= -0.000001) point.x = 0.00001;
    if(point.y <= 0.000001 && point.y >= -0.000001) point.y = 0.00001;
    if(point.z <= 0.000001 && point.z >= -0.000001) point.z = 0.00001;

    if(triangle_cart.p1_coord.x <= 0.000001 && triangle_cart.p1_coord.x >= -0.000001) triangle_cart.p1_coord.x = 0.00001;
    if(triangle_cart.p1_coord.y <= 0.000001 && triangle_cart.p1_coord.y >= -0.000001) triangle_cart.p1_coord.y = 0.00001;
    if(triangle_cart.p1_coord.z <= 0.000001 && triangle_cart.p1_coord.z >= -0.000001) triangle_cart.p1_coord.z = 0.00001;

    if(triangle_cart.p2_coord.x <= 0.000001 && triangle_cart.p2_coord.x >= -0.000001) triangle_cart.p2_coord.x = 0.00001;
    if(triangle_cart.p2_coord.y <= 0.000001 && triangle_cart.p2_coord.y >= -0.000001) triangle_cart.p2_coord.y = 0.00001;
    if(triangle_cart.p2_coord.z <= 0.000001 && triangle_cart.p2_coord.z >= -0.000001) triangle_cart.p2_coord.z = 0.00001;

    if(triangle_cart.p3_coord.x <= 0.000001 && triangle_cart.p3_coord.x >= -0.000001) triangle_cart.p3_coord.x = 0.00001;
    if(triangle_cart.p3_coord.y <= 0.000001 && triangle_cart.p3_coord.y >= -0.000001) triangle_cart.p3_coord.y = 0.00001;
    if(triangle_cart.p3_coord.z <= 0.000001 && triangle_cart.p3_coord.z >= -0.000001) triangle_cart.p3_coord.z = 0.00001;

    u.x = triangle_cart.p2_coord.x - triangle_cart.p1_coord.x;
    u.y = triangle_cart.p2_coord.y - triangle_cart.p1_coord.y;
    u.z = triangle_cart.p2_coord.z - triangle_cart.p1_coord.z;

    v.x = triangle_cart.p3_coord.x - triangle_cart.p1_coord.x;
    v.y = triangle_cart.p3_coord.y - triangle_cart.p1_coord.y;
    v.z = triangle_cart.p3_coord.z - triangle_cart.p1_coord.z;

    float alpha1 = (triangle_cart.p1_coord.z/point.z) - (triangle_cart.p1_coord.x/point.x);
    float alpha2 = (v.z/point.z) - (v.x/point.x);
    float alpha3 = (u.x/point.x) - (u.z/point.z);

    float beta1 = (triangle_cart.p1_coord.y/point.y) - (triangle_cart.p1_coord.x/point.x);
    float beta2 = (v.y/point.y) - (v.x/point.x);
    float beta3 = (u.x/point.x) - (u.y/point.y);

    float mu = (alpha3*beta1 -beta3*alpha1) / (beta3*alpha2 -alpha3*beta2);
    float lambda = (alpha1+alpha2*mu)/alpha3;
    projection_point.x = triangle_cart.p1_coord.x + lambda*u.x + mu*v.x;
    projection_point.y = triangle_cart.p1_coord.y + lambda*u.y + mu*v.y;
    projection_point.z = triangle_cart.p1_coord.z + lambda*u.z + mu*v.z;
}

void GeoMaths::productVectorial(const float *u, const float *v, float *result)
{
    result[0] = u[1]*v[2]-u[2]*v[1];
    result[1] = u[2]*v[0]-u[0]*v[2];
    result[2] = u[0]*v[1]-u[1]*v[0];
}

float GeoMaths::productScalar(const float *u, const float *v)
{
    float result;

    result = u[0]*v[0] + u[1]*v[1] + u[2]*v[2];

    return result;
}

float GeoMaths::distanceBetween(const Cartesianas &point, const Cartesianas &projection_point)
{
    float diff[3];
    diff[0] = point.x -projection_point.x;
    diff[1] = point.y -projection_point.y;
    diff[2] = point.z -projection_point.z;

    return sqrtf(powf(diff[0],2) + powf(diff[1],2) + powf(diff[2],2));
}

void GeoMaths::projectPointToSphere(Cartesianas &point, const float &radius)
{
    float lambda =  sqrtf( pow(radius,2)/( pow(point.x,2) + pow(point.y,2) + pow(point.z,2)) );

    point.x = lambda * point.x;
    point.y = lambda * point.y;
    point.z = lambda * point.z;
}

void GeoMaths::divideTriangleInFour(const TriangleCartesianas &origin_triangle, vertices &new_vertices, const float &radius)
{
    new_vertices.clear();

    Cartesianas cart12_middle = GeoMaths::getMiddleLatLonBetween(origin_triangle.p1_coord, origin_triangle.p2_coord);
    Cartesianas cart13_middle = GeoMaths::getMiddleLatLonBetween(origin_triangle.p1_coord, origin_triangle.p3_coord);
    Cartesianas cart23_middle = GeoMaths::getMiddleLatLonBetween(origin_triangle.p2_coord, origin_triangle.p3_coord);

    GeoMaths::projectPointToSphere(cart12_middle, radius);
    GeoMaths::projectPointToSphere(cart13_middle, radius);
    GeoMaths::projectPointToSphere(cart23_middle, radius);

    //vertices
    new_vertices.vertices_cartesianas.push_back(origin_triangle.p1_coord.x);
    new_vertices.vertices_cartesianas.push_back(origin_triangle.p1_coord.y);
    new_vertices.vertices_cartesianas.push_back(origin_triangle.p1_coord.z);

    new_vertices.vertices_cartesianas.push_back(origin_triangle.p2_coord.x);
    new_vertices.vertices_cartesianas.push_back(origin_triangle.p2_coord.y);
    new_vertices.vertices_cartesianas.push_back(origin_triangle.p2_coord.z);

    new_vertices.vertices_cartesianas.push_back(origin_triangle.p3_coord.x);
    new_vertices.vertices_cartesianas.push_back(origin_triangle.p3_coord.y);
    new_vertices.vertices_cartesianas.push_back(origin_triangle.p3_coord.z);

    new_vertices.vertices_cartesianas.push_back(cart12_middle.x);
    new_vertices.vertices_cartesianas.push_back(cart12_middle.y);
    new_vertices.vertices_cartesianas.push_back(cart12_middle.z);

    new_vertices.vertices_cartesianas.push_back(cart13_middle.x);
    new_vertices.vertices_cartesianas.push_back(cart13_middle.y);
    new_vertices.vertices_cartesianas.push_back(cart13_middle.z);

    new_vertices.vertices_cartesianas.push_back(cart23_middle.x);
    new_vertices.vertices_cartesianas.push_back(cart23_middle.y);
    new_vertices.vertices_cartesianas.push_back(cart23_middle.z);

    //triangle 1
    new_vertices.indices.push_back(0);
    new_vertices.indices.push_back(3);
    new_vertices.indices.push_back(4);
    //triangle 2
    new_vertices.indices.push_back(3);
    new_vertices.indices.push_back(5);
    new_vertices.indices.push_back(4);

    //triangle 3
    new_vertices.indices.push_back(3);
    new_vertices.indices.push_back(1);
    new_vertices.indices.push_back(5);

    //triangle 4
    new_vertices.indices.push_back(4);
    new_vertices.indices.push_back(5);
    new_vertices.indices.push_back(2);

}
