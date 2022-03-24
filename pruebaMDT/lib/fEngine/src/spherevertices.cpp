//#include "spherevertices.h"
//#include <math.h>


//SphereVertices::SphereVertices(float radius, int disAzimut, int disColat)
//{
//    m_array_xyz = new float[disAzimut*disColat*3];
//    m_array_ebo = new int[disAzimut*disColat];
//    m_radius = radius;
//    m_disAzimut = disAzimut;
//    m_disColat = disColat;
//}

//float *SphereVertices::getArray_xyz()
//{
//    return m_array_xyz;
//}

//void SphereVertices::createEBO()
//{
//    for (int i=0; i<m_disColat; i++)
//    {
//        for (int j=0; j<m_disAzimut; j++)
//        {
//            if (i==0 )
//            {
//                m_array_ebo[i*m_disColat+j+0] = 0;
//                m_array_ebo[i*m_disColat+j+1] = j + 1;
//                m_array_ebo[i*m_disColat+j+2] = j + 2;
//                continue;
//            }
//            else if (i==m_disAzimut-1)
//            {
//                m_array_ebo[i*m_disColat+j+0] = 0;
//                m_array_ebo[i*m_disColat+j+1] = j + 1;
//                m_array_ebo[i*m_disColat+j+2] = j + 2;
//                continue;
//            }

//            m_array_ebo[i*m_disColat+j+0]=j;
//            m_array_ebo[i*m_disColat+j+1]=j + m_disColat;
//            m_array_ebo[i*m_disColat+j+2]=j + m_disColat + 1;

//            m_array_ebo[i*m_disColat+j+3]=j;
//            m_array_ebo[i*m_disColat+j+4]=j + m_disColat + 1;
//            m_array_ebo[i*m_disColat+j+5]=j + 1;
//        }
//    }
//}

//void SphereVertices::createArray()
//{
//    for (int i=0; i<m_disColat; i++)
//    {
//        for (int j=0; j<m_disAzimut; j++)
//        {
//            float x = -m_radius*sin(360.0*float(i)/m_disColat);
//            float y =  m_radius*cos(360.0*float(i)/m_disColat);
//            float z =  m_radius*cos(360.0*float(j)/m_disAzimut);
//            m_array_xyz[i*m_disColat+j + 0] = x;
//            m_array_xyz[i*m_disColat+j + 1] = y;
//            m_array_xyz[i*m_disColat+j + 2] = z;

//            if (i==0 )
//            {
//                i++;
//            }
//            else if (i==m_disAzimut-1)
//            {
//                break;
//            }
//            else
//            {
//                continue;
//            }


//        }
//    }
//}
