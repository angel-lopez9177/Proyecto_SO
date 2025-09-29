#ifndef PROCESO_H
#define PROCESO_H

#include <QString>

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
        int tiempoEstimado;
        int ID;
        int tiempoTranscurrido;
        int tiempoBloqueado;

        Proceso() : numero1(0), indiceOperacion(0), numero2(0), tiempoEstimado(0), ID(0), tiempoTranscurrido(0), tiempoBloqueado(0) {}
        Proceso(int num1, int indiceOp, int num2, int TE, int id) : numero1(num1), indiceOperacion(indiceOp), numero2(num2), tiempoEstimado(TE), ID(id), tiempoTranscurrido(0), tiempoBloqueado(0) {}
};


#endif