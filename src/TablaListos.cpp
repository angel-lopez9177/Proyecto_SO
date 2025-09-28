#include "TablaListos.h"

TablaListos::TablaListos(QWidget *tabla) : TablaBase(tabla) {}

void TablaListos::actualizar(const std::deque<Proceso>& procesosListos) {
    this->limpiar();
    this->setRowCount(procesosListos.size());
    int fila = 0;
    for (const auto& proceso : procesosListos) {
        this->setItem(fila, 0, new QTableWidgetItem(QString::number(proceso.ID)));
        this->setItem(fila, 1, new QTableWidgetItem(QString::number(proceso.tiempoEstimado)));
        this->setItem(fila, 2, new QTableWidgetItem(QString::number(proceso.tiempoTranscurrido / 1000.0)));
        fila++;
    }
}

void TablaListos::agregar(const int fila, const Proceso& proceso){
    if (fila < 0 || fila > this->rowCount()) {
        return;
    }
    this->insertRow(fila);
    this->setItem(fila, 0, new QTableWidgetItem(QString::number(proceso.ID)));
    this->setItem(fila, 1, new QTableWidgetItem(QString::number(proceso.tiempoEstimado)));
    this->setItem(fila, 2, new QTableWidgetItem(QString::number(proceso.tiempoTranscurrido / 1000.0)));
}

void TablaListos::pushBack(const Proceso& proceso) {
    int fila = this->rowCount();
    this->insertRow(fila);
    this->setItem(fila, 0, new QTableWidgetItem(QString::number(proceso.ID)));
    this->setItem(fila, 1, new QTableWidgetItem(QString::number(proceso.tiempoEstimado)));
    this->setItem(fila, 2, new QTableWidgetItem(QString::number(proceso.tiempoTranscurrido / 1000.0)));
}

void TablaListos::pushFront(const Proceso& proceso) {
    this->insertRow(0);
    this->setItem(0, 0, new QTableWidgetItem(QString::number(proceso.ID)));
    this->setItem(0, 1, new QTableWidgetItem(QString::number(proceso.tiempoEstimado)));
    this->setItem(0, 2, new QTableWidgetItem(QString::number(proceso.tiempoTranscurrido / 1000.0)));
}

