#ifndef VENTANACANTIDAD_H
#define VENTANACANTIDAD_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QMessageBox>

struct Datos{

    int selectedQuantity;
    int quantumTiempo;

    Datos(int x, int y) : selectedQuantity(x), quantumTiempo(y) {}
};

class VentanaCantidad : public QDialog
{
    Q_OBJECT

public:
    explicit VentanaCantidad();
    ~VentanaCantidad();

    static Datos datos;
    static Datos getQuantity();

private slots:
    void onConfirmClicked();

private:
    QSpinBox *spinBox_procesos;
    QSpinBox *spinBox_quantum;
    QPushButton *confirmButton;

};

#endif // VENTANACANTIDAD_H