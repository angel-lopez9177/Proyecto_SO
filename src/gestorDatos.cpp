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

        int operacion = QRandomGenerator::global()->bounded(-1,6);

        int valor1 = QRandomGenerator::global()->bounded(-1,100);
        int valor2 = 0;
        int tiempoEstimado = QRandomGenerator::global()->bounded(5,21) * 1000;

        if (operacion == Proceso::DIVISION || operacion == Proceso::MODULO){
                valor2 = QRandomGenerator::global()->bounded(0,100);
        }else{
                valor2 = QRandomGenerator::global()->bounded(-1,100);
        }

        Proceso proceso(valor1, operacion, valor2, tiempoEstimado, ID);
        
        return proceso;
}
