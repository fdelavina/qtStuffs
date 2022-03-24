#include "qoctal.h"

FOctal::FOctal(QString string)
{
    this->m_octal = string;
}

FOctal::FOctal()
{
    this->m_octal = "";
}

void FOctal::setOctal(QString octalnumber)
{
    this->m_octal = octalnumber;
}

QString FOctal::getOctal()
{
    return m_octal;
}
