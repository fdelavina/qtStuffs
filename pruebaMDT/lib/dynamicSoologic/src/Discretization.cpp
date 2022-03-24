#include "Discretization.h"

Discretization::Discretization(unsigned int num_sectors)
{
    m_num_sectors = num_sectors;
    setDiscretitation();
}

void Discretization::setDiscretitation()
{
    Altitud altitud_res;
    Longitud longitud_res;

    for (unsigned int i = 0; i<m_num_sectors; i++)
    {
        float latitud  = altitud_res .min_value +180.0*(float(i)/(m_num_sectors-1));
        float longitud = longitud_res.min_value +360.0*(float(i)/(m_num_sectors-1));
        m_center_mdt_latitud.append(latitud);
        m_center_mdt_longitud.append(longitud);
    }
}

QVector<double> Discretization::getLatitude()
{
    return m_center_mdt_latitud;
}

QVector<double> Discretization::getLongitude()
{
    return m_center_mdt_longitud;
}
