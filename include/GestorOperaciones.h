#ifndef GESTOROPERACIONES_H
#define GESTOROPERACIONES_H

#include "Proceso.h"
#include <QString>
#include <cmath>

class GestorOperaciones
{
        public:
        enum Operacion {
                SUMA = 0,              // "+"
                RESTA = 1,             // "-"
                MULTIPLICACION = 2,    // "*"
                DIVISION = 3,          // "/"
                MODULO = 4,            // "%"
                POTENCIA = 5           // "^"
        };
        static QString generarOperacionMatematica(const Proceso& proceso);
        static QString calcularResultado(const Proceso& proceso);
};

#endif