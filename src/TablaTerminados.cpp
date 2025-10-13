#include "TablaTerminados.h"

TablaTerminados::TablaTerminados(QWidget *tabla) : TablaBase(tabla) {}

void TablaTerminados::agregarProceso(const Proceso& proceso, const QString& operacion, const QString& resultado) {
    int fila = this->rowCount();
    this->insertRow(fila);
    this->setItem(fila, 0, new QTableWidgetItem(QString::number(proceso.ID)));
    this->setItem(fila, 1, new QTableWidgetItem(operacion));
    this->setItem(fila, 2, new QTableWidgetItem(resultado));
}