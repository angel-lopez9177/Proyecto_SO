#include "VentanaCantidad.h"

Datos VentanaCantidad::datos(1,1); 

VentanaCantidad::VentanaCantidad()
    : QDialog(nullptr)
{
    setWindowTitle("Cantidad de Procesos");
    setModal(false);
    setFixedSize(300, 150);

    QLabel *label_1 = new QLabel("Ingresa cantidad de procesos:", this);
    spinBox_procesos = new QSpinBox(this);
    QLabel *label_2 = new QLabel("Ingresa Quantum de Tiempo:", this);
    spinBox_quantum = new QSpinBox(this);
    confirmButton = new QPushButton("Confirmar", this);

    spinBox_procesos->setMinimum(1);
    spinBox_procesos->setMaximum(100); 
    spinBox_procesos->setValue(1);
    spinBox_quantum->setMinimum(1);
    spinBox_quantum->setMaximum(100); 
    spinBox_quantum->setValue(1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *spinLayout_1 = new QHBoxLayout();
    QHBoxLayout *spinLayout_2 = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    spinLayout_1->addWidget(label_1);
    spinLayout_1->addWidget(spinBox_procesos);
    spinLayout_2->addWidget(label_2);
    spinLayout_2->addWidget(spinBox_quantum);

    buttonLayout->addStretch();
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(spinLayout_1);
    mainLayout->addStretch();
    mainLayout->addLayout(spinLayout_2);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    connect(confirmButton, &QPushButton::clicked, this, &VentanaCantidad::onConfirmClicked);
    connect(spinBox_procesos, QOverload<int>::of(&QSpinBox::valueChanged), 
            [this](int value) { datos.selectedQuantity = value; });
    connect(spinBox_quantum, QOverload<int>::of(&QSpinBox::valueChanged), 
            [this](int value) { datos.quantumTiempo = value; });
}

VentanaCantidad::~VentanaCantidad()
{
}

void VentanaCantidad::onConfirmClicked()
{
    accept();
}

Datos VentanaCantidad::getQuantity()
{
    VentanaCantidad dialog;
    
    if (dialog.exec() == QDialog::Accepted) {
        return datos;
    }
    return Datos(-1,-1);
}