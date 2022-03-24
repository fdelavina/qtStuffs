#ifndef ICOSPHERE_H
#define ICOSPHERE_H
#include <vector>
#include "globalLib/Global/globalLib.h"

struct DYNAMICSOOLOGIC_EXPORT vertices
{
    std::vector<float> vertices;
    std::vector<int> indices;
};

class DYNAMICSOOLOGIC_EXPORT IcoSphere
{
public:
    IcoSphere(float radius);
    void runOriginalIco(float radius);

    //getter
    vertices getOriginalVertices();
private:
    //meth
    void setOriginalIco();

    //atr
    vertices m_original_ico;
    float m_radius;
};

#endif // ICOSPHERE_H
