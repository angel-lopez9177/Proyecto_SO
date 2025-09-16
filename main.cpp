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

    auto procesos = GestorDatos::obtener_procesos(cantidad);
    if(!procesos.has_value()){
        return 0;
    }

    std::vector<Proceso> listaProcesos = procesos.value();

    for (size_t i = 0; i < listaProcesos.size(); i++) {
    const auto& proceso = listaProcesos[i];
    std::cout << "Proceso " << (i + 1) << ": " << " (TE: " << proceso.tiempoEstimado
                << ", N1: " << proceso.numero1
                << ", OP: " << proceso.indiceOperacion
                << ", N2: " << proceso.numero2 
                << ", ID: " << proceso.ID << ")" << std::endl;
    }

    window.show();
    window.setFocus();
    window.setProcesos(listaProcesos);
    window.comenzarEjecucion();
    
    return app.exec();
}