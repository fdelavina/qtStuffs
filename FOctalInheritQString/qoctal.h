#ifndef QOCTAL_H
#define QOCTAL_H

#include <QString>

class FOctal
{
public:
    FOctal(QString string);
    FOctal();

    void setOctal(QString octalnumber);
    QString getOctal();
private:
    void toOctal(QString str);

private:
    QString m_octal;


};

#endif // QOCTAL_H
