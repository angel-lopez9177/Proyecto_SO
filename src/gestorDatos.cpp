#include "gestorDatos.h"
#include "VentanaDatos.h"
#include <iostream>

std::optional<std::vector<Programa>> GestorDatos::obtener_programas(int cantidad)
{
    std::vector<Programa> programas;
    
    for (int i = 0; i < cantidad; i++) {
        std::cout << "Solicitando datos del programa " << (i + 1) << " de " << cantidad << std::endl;
        
        auto programaOpt = VentanaDatos::obtener_datos();
        
        if (programaOpt.has_value()) {
            programas.push_back(programaOpt.value());
            std::cout << "Programa agregado" << std::endl;
        } else {
            std::cout << "Usuario canceló" << std::endl;
            return std::nullopt;
        }
    }
    
    return programas;
}
