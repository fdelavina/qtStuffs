#ifndef OPERACION_H
#define OPERACION_H

#include "Global/globalLib.h"

class LIB1SHARED_EXPORT Operacion
{
private:
    int result;
public:
    Operacion();

    int LIB1SHARED_EXPORT suma(int a,int b);
    int LIB1SHARED_EXPORT resta(int a,int b);


};

#endif // OPERACION_H
