#include "TablaEjecucion.h"

TablaEjecucion::TablaEjecucion(QWidget *tabla) : TablaBase(tabla) {
    this->setRowCount(5);
}

void TablaEjecucion::mostrarProceso(const Proceso& proceso, const QString& operacion) {
    this->setItem(0, 0, new QTableWidgetItem(QString::number(proceso.ID)));
    this->setItem(1, 0, new QTableWidgetItem(operacion));
    this->setItem(2, 0, new QTableWidgetItem(QString::number(proceso.tiempoEstimado)));
    actualizarTiempos(proceso);
}

void TablaEjecucion::actualizarTiempos(const Proceso& proceso) {
    float tiempoRestante = proceso.tiempoEstimado * 1000 - proceso.tiempoTranscurrido;
    this->setItem(3, 0, new QTableWidgetItem(QString::number(proceso.tiempoTranscurrido / 1000.0, 'f', 2)));
    this->setItem(4, 0, new QTableWidgetItem(QString::number(tiempoRestante / 1000.0, 'f', 2)));
}

void TablaEjecucion::limpiar() {
    for (int i = 0; i < this->rowCount(); ++i) {
        this->setItem(i, 0, new QTableWidgetItem(""));
    }
}