#include <iostream>

#include "operacion/operacion.h"


using namespace std;


int main()
{

    Operacion MiOperacion;

    int resultado;
    resultado = MiOperacion.suma(4,2);

    cout << resultado << endl;
    return 0;
}
