#include <iostream>
#include <QApplication>
#include <QWidget>
#include "MainWindow.h"
#include "VentanaCantidad.h"
#include "VentanaDatos.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);  
    
    MainWindow window; 
     
    int cantidad = VentanaCantidad::getQuantity();
    if (cantidad == -1) return 0;

    VentanaDatos::obtener_datos();

    window.show();  
    return app.exec();
}