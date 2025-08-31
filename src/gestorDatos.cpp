#include "gestorDatos.h"
#include "VentanaDatos.h"
#include <iostream>
#include <QMessageBox>

std::optional<std::vector<Programa>> GestorDatos::obtener_programas(int cantidad)
{
    std::vector<Programa> programas;
    
    
    for (int i = 0; i < cantidad; i++) {
        std::cout << "Solicitando datos del programa " << (i + 1) << " de " << cantidad << std::endl;
        
        auto programaOpt = VentanaDatos::obtener_datos();
        
        bool IDRepetida = false;

        if (programaOpt.has_value()) {
                for(int i = 0; i<programas.size();i++){
                        if (programaOpt.value().ID == programas[i].ID) IDRepetida = true;
                }
                if (IDRepetida){
                        i--; 
                        QMessageBox mensaje;
                        mensaje.setWindowTitle("Error");
                        mensaje.setText("El ID debe de ser unico, reingrese los datos");
                        mensaje.exec();
                        continue;
                } 
                programas.push_back(programaOpt.value());
                std::cout << "Programa agregado" << std::endl;
        }else {
                std::cout << "Usuario canceló" << std::endl;
                return std::nullopt;
        }
    }
    
    return programas;
}
