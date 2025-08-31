#include "VentanaCantidad.h"
#include <QMessageBox>

VentanaCantidad::VentanaCantidad()
    : QDialog(nullptr), selectedQuantity(1)
{
    setWindowTitle("Cantidad de Programas");
    setModal(false);
    setFixedSize(300, 150);

    QLabel *label = new QLabel("Ingresa cantidad de programas:", this);
    spinBox = new QSpinBox(this);
    confirmButton = new QPushButton("Confirmar", this);

    spinBox->setMinimum(1);
    spinBox->setMaximum(100); 
    spinBox->setValue(1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *spinLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    spinLayout->addWidget(label);
    spinLayout->addWidget(spinBox);

    buttonLayout->addStretch();
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(spinLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(confirmButton, &QPushButton::clicked, this, &VentanaCantidad::onConfirmClicked);
    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            [this](int value) { selectedQuantity = value; });
}

VentanaCantidad::~VentanaCantidad()
{
}

void VentanaCantidad::onConfirmClicked()
{
    accept();
}

int VentanaCantidad::getQuantity()
{
    VentanaCantidad dialog;
    
    if (dialog.exec() == QDialog::Accepted) {
        return dialog.spinBox->value();
    }
    
    return -1;
}