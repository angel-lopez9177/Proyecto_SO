#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // Inicializar aplicación Qt
    
    MainWindow window;  // Crear tu ventana principal
    window.show();      // Mostrar la ventana
    
    return app.exec();  // Ejecutar el bucle principal
}