#ifndef VENTANADATOS_H
#define VENTANADATOS_H

#include <QWidget>

namespace Ui {
class VentanaDatos;
}

class VentanaDatos : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaDatos(QWidget *parent = nullptr);
    ~VentanaDatos();

private:
    Ui::VentanaDatos *ui;  // Puntero a tu interfaz generada
};



#endif