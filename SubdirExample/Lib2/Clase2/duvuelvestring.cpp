#include "duvuelvestring.h"

duvuelveString::duvuelveString(std::string _nombre)
{
    this->nombre = _nombre;
}

std::string duvuelveString::devuelvo()
{
    std::string texto = "hola me llamo " + this->nombre;

    return texto;
}
