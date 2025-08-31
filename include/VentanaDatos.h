#ifndef VENTANADATOS_H
#define VENTANADATOS_H

#include <QWidget>
#include "Programa.h"

namespace Ui {
class VentanaDatos;
}

class VentanaDatos : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaDatos(QWidget *parent = nullptr);
    ~VentanaDatos();

    enum Operacion {
        SUMA = 0,              // "+"
        RESTA = 1,             // "-"
        MULTIPLICACION = 2,    // "*"
        DIVISION = 3,          // "/"
        MODULO = 4,            // "%"
        POTENCIA = 5           // "^"
    };

    static std::optional<Programa> obtener_datos();

public slots:
    void boton_aceptar_clicked();

signals:
    void datosListos(Programa programa);
    void usuarioCancelo();


private:
    Ui::VentanaDatos *ui;
    static std::optional<Programa> resultadoStatico;
};



#endif