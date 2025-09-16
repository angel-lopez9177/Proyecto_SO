#ifndef PROCESO_H
#define PROCESO_H

#include <QString>
#include <optional>

struct Proceso
{
        enum Operacion {
                SUMA = 0,              // "+"
                RESTA = 1,             // "-"
                MULTIPLICACION = 2,    // "*"
                DIVISION = 3,          // "/"
                MODULO = 4,            // "%"
                POTENCIA = 5           // "^"
        };

        int numero1;
        int indiceOperacion;
        int numero2;
        float tiempoEstimado;
        int ID;
        float tiempoTranscurrido;
};


#endif