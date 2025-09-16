#include "gestorDatos.h"
#include "VentanaDatos.h"
#include <iostream>
#include <QMessageBox>
#include <QRandomGenerator>

std::list<Proceso> GestorDatos::obtener_procesos(int cantidad)
{
    std::list<Proceso> procesos;
    
    for (int i = 0; i < cantidad; i++) {
        
        Proceso procesoOpt = GestorDatos::generar_proceso(i + 1);

        procesos.push_back(procesoOpt);
    }
    
    return procesos;
}

Proceso GestorDatos::generar_proceso(int ID){
        Proceso proceso;

        int operacion = QRandomGenerator::global()->bounded(-1,6);

        int valor1 = QRandomGenerator::global()->bounded(-1,100);
        int valor2 = 0;
        float tiempoEstimado = QRandomGenerator::global()->bounded(5,21) * 1.0;
        float tiempoTranscurrido = 0.0;

        if (operacion == Proceso::DIVISION || operacion == Proceso::MODULO){
                valor2 = QRandomGenerator::global()->bounded(0,100);
        }else{
                valor2 = QRandomGenerator::global()->bounded(-1,100);
        }

        proceso.tiempoEstimado = tiempoEstimado;
        proceso.indiceOperacion = operacion;
        proceso.ID = ID;
        proceso.tiempoTranscurrido = tiempoTranscurrido;
        proceso.numero1 = valor1;
        proceso.numero2 = valor2;

        return proceso;
}
