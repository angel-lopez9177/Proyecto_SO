#include <iostream>
#include <QApplication>
#include <QWidget>
#include "MainWindow.h"
#include "VentanaCantidad.h"
#include "VentanaDatos.h"
#include "gestorDatos.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);  
    
    MainWindow window; 
     
    int cantidad = VentanaCantidad::getQuantity();
    if (cantidad == -1) return 0;

    auto programas = GestorDatos::obtener_programas(cantidad);
    if(!programas.has_value()){
        return 0;
    }

    std::vector<Programa> listaProgramas = programas.value();

    for (size_t i = 0; i < listaProgramas.size(); i++) {
    const auto& programa = listaProgramas[i];
    std::cout << "Programa " << (i + 1) << ": " << programa.nombreProgramador.toStdString()
                << " (TE: " << programa.tiempoEstimado
                << ", N1: " << programa.numero1
                << ", OP: " << programa.indiceOperacion
                << ", N2: " << programa.numero2 
                << ", ID: " << programa.ID << ")" << std::endl;
    }

    window.show();

    
    return app.exec();
}