#ifndef PROCESO_H
#define PROCESO_H

#include <QString>
#include <QList>

struct Proceso
{

        int numero1;
        int indiceOperacion;
        int numero2;
        int tiempoEstimado;
        int ID;
        int tiempoTranscurrido;
        int tiempoBloqueado;
        int tiempoLlegada;
        int tiempoFinalizacion;
        int tiempoPrimerServicio;
        int tamano;          
        int cantidadPaginas; 
        QList<int> marcosAsignados;

        Proceso() : numero1(0), indiceOperacion(0), numero2(0), tiempoEstimado(0), ID(0), tiempoTranscurrido(0), tiempoBloqueado(0), tiempoLlegada(-1), tiempoFinalizacion(-1), tiempoPrimerServicio(-1), tamano(0), cantidadPaginas(0) {}
        Proceso(int num1, int indiceOp, int num2, int TE, int id) : numero1(num1), indiceOperacion(indiceOp), numero2(num2), tiempoEstimado(TE), ID(id), tiempoTranscurrido(0), tiempoBloqueado(0), tiempoLlegada(-1), tiempoFinalizacion(-1), tiempoPrimerServicio(-1), tamano(0), cantidadPaginas(0) {}
};


#endif