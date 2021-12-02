#ifndef DUVUELVESTRING_H
#define DUVUELVESTRING_H

#include <iostream>
#include <Global/globalLib.h>

using namespace std;


class LIB2SHARED_EXPORT duvuelveString
{
private:
    std::string nombre;
public:
    duvuelveString(std::string);

    std::string LIB2SHARED_EXPORT devuelvo();
};

#endif // DUVUELVESTRING_H




