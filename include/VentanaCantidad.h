#ifndef VENTANACANTIDAD_H
#define VENTANACANTIDAD_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

class VentanaCantidad : public QDialog
{
    Q_OBJECT

public:
    explicit VentanaCantidad();
    ~VentanaCantidad();

    static int getQuantity();

private slots:
    void onConfirmClicked();

private:
    QSpinBox *spinBox;
    QPushButton *confirmButton;
    int selectedQuantity;
};

#endif // VENTANACANTIDAD_H