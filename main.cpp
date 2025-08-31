#include <iostream>
#include <QApplication>
#include <QWidget>
#include "MainWindow.h"
#include "VentanaCantidad.h"
#include "VentanaDatos.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);  // Inicializar aplicación Qt
    
    MainWindow window;  // Crear tu ventana principal

    int cantidad = VentanaCantidad::getQuantity();
    std::cout << cantidad;
    window.show();      // Mostrar la ventana
    
    return app.exec();  // Ejecutar el bucle principal
}