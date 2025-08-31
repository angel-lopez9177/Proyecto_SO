#include "VentanaDatos.h"
#include "ui_VentanaDatos.h"

VentanaDatos::VentanaDatos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VentanaDatos)
{
    ui->setupUi(this);
}

VentanaDatos::~VentanaDatos()
{
    delete ui;
}