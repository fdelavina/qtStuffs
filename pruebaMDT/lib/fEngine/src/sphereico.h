#ifndef SPHEREICO_H
#define SPHEREICO_H
#include <math.h>
#include <vector>
#include <map>
#include "globalLib/Global/globalLib.h"

class FENGINE_EXPORT SphereIco
{
public:
    SphereIco(float radius, int sub, bool smooth);
    SphereIco();

    std::vector<float> getVertices()
    {
        return vertices;
    }
    int getNumberVertices()
    {
        return vertices.size()/3;
    }
    int getSizeVerticesVector()
    {
        return vertices.size();
    }
    std::vector<unsigned int> getElements()
    {
        return indices;
    }
    int getNumberElements()
    {
        return indices.size()/3;
    }
    int getSizeElements()
    {
        return indices.size();
    }
    float getDistanceVertices()
    {
        std::vector<float> vertice1;
        vertice1.push_back(vertices[0]);
        vertice1.push_back(vertices[1]);
        vertice1.push_back(vertices[2]);
        std::vector<float> vertice2;
        vertice2.push_back(vertices[3]);
        vertice2.push_back(vertices[4]);
        vertice2.push_back(vertices[5]);
        return getDistanceBetweenTwoPoints(vertice1,vertice2);
    }
    std::vector<float> getVerticesInfluence()
    {
        return vertices_in_influence;
    }

    int getSizeVerticesInfluenceVector()
    {
        return vertices_in_influence.size();
    }

    void setInfluenceVerticesInRadius(float lat, float lon, float radius);

private:
    // static
    static void computeFaceNormal(const float v1[3], const float v2[3], const float v3[3], float normal[3]);
    static void computeVertexNormal(const float v[3], float normal[3]);
    static float computeScaleForLength(const float v[3], float length);
    // member func
    void buildVerticesSmooth();
    void buildVerticesFlat();
    void buildVerticesFlatPolar();
    std::vector<float> computeIcosahedronVertices();
    void subdivideVerticesSmooth();
    void subdivideVerticesFlat();
    void buildInterleavedVertices();

    float getDistanceBetweenTwoPoints(std::vector<float>reference1, std::vector<float>  reference2);

    void addVertex(float x, float y, float z);
    void addNormal(float nx, float ny, float nz);
    void addTexCoord(float s, float t);

    void addVertices(const float v1[3], const float v2[3], const float v3[3]);
    void addNormals(const float n1[3], const float n2[3], const float n3[3]);
    void addTexCoords(const float t1[2], const float t2[2], const float t3[2]);
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
    void addSubLineIndices(unsigned int i1, unsigned int i2,unsigned int i3,unsigned int i4,unsigned int i5,unsigned int i6);
    unsigned int addSubVertexAttribs(const float v[3], const float n[3], const float t[2]);
    void computeHalfVertex(const float v1[3], const float v2[3], float length, float newV[3]);
    void computeHalfTexCoord(const float t1[2], const float t2[2], float newT[2]);

    bool isSharedTexCoord(const float t[2]);
    bool isOnLineSegment(const float a[2], const float b[2], const float c[2]);
    // member vars
      float radius;                           // circumscribed radius
      int subdivision;
      bool smooth;
      float m_distance_between_points;
      std::vector<float> vertices;
      std::vector<float> vertices_geo;
      std::vector<float> vertices_in_influence;
      std::vector<float> normals;
      std::vector<float> texCoords;
      std::vector<unsigned int> indices;
      std::vector<unsigned int> lineIndices;
      std::map<std::pair<float, float>, unsigned int> sharedIndices;   // indices of shared vertices, key is tex coord (s,t)

      // interleaved
      std::vector<float> interleavedVertices;
      int interleavedStride;                  // # of bytes to hop to the next vertex (should be 32 bytes)
};

#endif // SPHEREICO_H
