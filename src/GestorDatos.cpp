#include "GestorDatos.h"
#include "GestorOperaciones.h"
#include "VentanaDatos.h"
#include <iostream>
#include <QMessageBox>
#include <QRandomGenerator>

int GestorDatos::ID = 0;

QList<Proceso> GestorDatos::obtener_procesos(int cantidad)
{
    QList<Proceso> procesos;
    for (int i = 0; i < cantidad; i++) {
        Proceso procesoOpt = GestorDatos::generar_proceso();
        procesos.push_back(procesoOpt);
        ID++;
    }
    return procesos;
}

Proceso GestorDatos::generar_proceso(){
        int operacion = QRandomGenerator::global()->bounded(6);

        int valor1 = QRandomGenerator::global()->bounded(100);
        int valor2 = 0;
        int tiempoEstimado = QRandomGenerator::global()->bounded(6,21) * 1000;

        if (operacion == GestorOperaciones::DIVISION || operacion == GestorOperaciones::MODULO){
                valor2 = QRandomGenerator::global()->bounded(1,100);
        }else{
                valor2 = QRandomGenerator::global()->bounded(100);
        }

        Proceso proceso(valor1, operacion, valor2, tiempoEstimado, ID);
        
        return proceso;
}
