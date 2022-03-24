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
}

vertices IcoSphere::getOriginalVertices()
{
    return m_original_ico;
}

void IcoSphere::setOriginalIco()
{
    //first point
    m_original_ico.vertices.push_back(0.0);      //x
    m_original_ico.vertices.push_back(0.0);      //y
    m_original_ico.vertices.push_back(m_radius); //z

    for (int i=0;i<5;i++)
    {
        float x = m_radius*cosf(2*M_PI*float(i)/5);
        float y = m_radius*sinf(2*M_PI*float(i)/5);
        float z = m_radius/2.0;
        m_original_ico.vertices.push_back(x); //x
        m_original_ico.vertices.push_back(y); //y
        m_original_ico.vertices.push_back(z); //z
    }

    for (int i=0;i<5;i++)
    {
        float x =   m_radius*cosf(2*M_PI*float(i)/5 +(M_PI/180.0)*36);
        float y =   m_radius*sinf(2*M_PI*float(i)/5 +(M_PI/180.0)*36);
        float z = - m_radius/2.0;
        m_original_ico.vertices.push_back(x); //x
        m_original_ico.vertices.push_back(y); //y
        m_original_ico.vertices.push_back(z); //z
    }

    //last point
    m_original_ico.vertices.push_back(0.0);      //x
    m_original_ico.vertices.push_back(0.0);      //y
    m_original_ico.vertices.push_back(-m_radius); //z


    //indices
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(2);m_original_ico.indices.push_back(1);
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(3);m_original_ico.indices.push_back(2);
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(4);m_original_ico.indices.push_back(3);
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(5);m_original_ico.indices.push_back(4);
    m_original_ico.indices.push_back(0);m_original_ico.indices.push_back(1);m_original_ico.indices.push_back(5);

    m_original_ico.indices.push_back(1);m_original_ico.indices.push_back(6);m_original_ico.indices.push_back(10);
    m_original_ico.indices.push_back(1);m_original_ico.indices.push_back(2); m_original_ico.indices.push_back(6);
    m_original_ico.indices.push_back(2);m_original_ico.indices.push_back(7); m_original_ico.indices.push_back(6);
    m_original_ico.indices.push_back(2);m_original_ico.indices.push_back(3); m_original_ico.indices.push_back(7);
    m_original_ico.indices.push_back(3);m_original_ico.indices.push_back(8); m_original_ico.indices.push_back(7);
    m_original_ico.indices.push_back(3);m_original_ico.indices.push_back(4); m_original_ico.indices.push_back(8);
    m_original_ico.indices.push_back(4);m_original_ico.indices.push_back(9); m_original_ico.indices.push_back(8);
    m_original_ico.indices.push_back(4);m_original_ico.indices.push_back(5); m_original_ico.indices.push_back(9);
    m_original_ico.indices.push_back(5);m_original_ico.indices.push_back(10) ;m_original_ico.indices.push_back(9);
    m_original_ico.indices.push_back(5);m_original_ico.indices.push_back(1);m_original_ico.indices.push_back(10);

    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(10); m_original_ico.indices.push_back(6);
    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(6); m_original_ico.indices.push_back(7);
    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(7); m_original_ico.indices.push_back(8);
    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(8); m_original_ico.indices.push_back(9);
    m_original_ico.indices.push_back(11);m_original_ico.indices.push_back(9);m_original_ico.indices.push_back(10);
}
