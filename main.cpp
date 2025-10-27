#include <iostream>
#include <QApplication>
#include <QWidget>
#include "MainWindow.h"
#include "VentanaCantidad.h"
#include "VentanaDatos.h"
#include "GestorDatos.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  
    
    MainWindow window; 
    Datos cantidad = VentanaCantidad::getQuantity();
    if (cantidad.selectedQuantity == -1 || cantidad.quantumTiempo == -1) return 0;

    auto listaProcesos = GestorDatos::obtener_procesos(cantidad.selectedQuantity);

    int i = 0;
    for (Proceso proceso : listaProcesos) {
        std::cout << "Proceso " << (++i) << ": " << " (TE: " << proceso.tiempoEstimado
                    << ", N1: " << proceso.numero1
                    << ", OP: " << proceso.indiceOperacion
                    << ", N2: " << proceso.numero2 
                    << ", ID: " << proceso.ID << ")" << std::endl;
    }

    window.show();
    window.setFocus();
    window.setProcesos(listaProcesos);
    window.setQuantum(cantidad.quantumTiempo);
    window.comenzarEjecucion();
    
    return app.exec();
}