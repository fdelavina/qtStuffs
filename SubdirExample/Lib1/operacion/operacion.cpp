#include "operacion.h"

Operacion::Operacion()
{
    this->result = 0;
}

int Operacion::suma(int a, int b)
{
    this->result = a + b;
    return this->result;

}

int Operacion::resta(int a, int b)
{
    this->result = a - b;
    return this->result;
}
