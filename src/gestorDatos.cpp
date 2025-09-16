#include "gestorDatos.h"
#include "VentanaDatos.h"
#include <iostream>
#include <QMessageBox>
#include <QRandomGenerator>

std::optional<std::vector<Programa>> GestorDatos::obtener_programas(int cantidad)
{
    std::vector<Programa> programas;
    
    for (int i = 0; i < cantidad; i++) {
        
        Programa programaOpt = GestorDatos::generar_programa(i + 1);

        programas.push_back(programaOpt);
    }
    
    return programas;
}

Programa GestorDatos::generar_programa(int ID){
        Programa programa;

        int operacion = QRandomGenerator::global()->bounded(-1,6);

        int valor1 = QRandomGenerator::global()->bounded(-1,100);
        int valor2 = 0;
        float tiempoEstimado = QRandomGenerator::global()->bounded(5,21) * 1.0;
        float tiempoTranscurrido = 0.0;

        if (operacion == Programa::DIVISION || operacion == Programa::MODULO){
                valor2 = QRandomGenerator::global()->bounded(0,100);
        }else{
                valor2 = QRandomGenerator::global()->bounded(-1,100);
        }

        programa.tiempoEstimado = tiempoEstimado;
        programa.indiceOperacion = operacion;
        programa.ID = ID;
        programa.tiempoTranscurrido = tiempoTranscurrido;
        programa.numero1 = valor1;
        programa.numero2 = valor2;

        return programa;
}
