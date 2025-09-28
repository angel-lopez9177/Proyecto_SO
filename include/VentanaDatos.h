#ifndef VENTANADATOS_H
#define VENTANADATOS_H

#include <QWidget>
#include "Proceso.h"

namespace Ui {
class VentanaDatos;
}

class VentanaDatos : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaDatos(QWidget *parent = nullptr);
    ~VentanaDatos();

    static std::optional<Proceso> obtener_datos();

public slots:
    void boton_aceptar_clicked();

signals:
    void datosListos(Proceso proceso);
    void usuarioCancelo();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::VentanaDatos *ui;
    static std::optional<Proceso> resultadoStatico;
};



#endif