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

    window.show();  
    return app.exec();
}