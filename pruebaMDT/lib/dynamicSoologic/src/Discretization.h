#ifndef DISCRETIZATION_H
#define DISCRETIZATION_H
#include <QVector>
#include "globalLib/Global/globalLib.h"

using vectorAngle = QVector<double> ;


struct Altitud
{
    float min_value = -90.0;
    float max_value =  90.0;
};
struct Longitud
{
    float min_value = -180.0;
    float max_value =  180.0;
};

class DYNAMICSOOLOGIC_EXPORT Discretization
{
public:
    Discretization(unsigned int num_sectors);

    void setDiscretitation();
    QVector<double>  getLongitude();
    QVector<double>  getLatitude();
private:
    QVector<double>  m_center_mdt_latitud ; // -90 a 90
    QVector<double>  m_center_mdt_longitud; // -180 a 180
    float m_range;
    unsigned int m_num_sectors;

};

#endif // DISCRETIZATION_H
