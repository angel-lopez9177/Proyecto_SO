#include "TablaListos.h"

TablaListos::TablaListos(QWidget *tabla) : TablaBase(tabla) {}

void TablaListos::actualizar(const std::deque<Proceso>& procesosListos) {
    this->setRowCount(procesosListos.size());
    int fila = 0;
    for (const auto& proceso : procesosListos) {
        this->setItem(fila, 0, new QTableWidgetItem(QString::number(proceso.ID)));
        this->setItem(fila, 1, new QTableWidgetItem(QString::number(proceso.tiempoEstimado)));
        this->setItem(fila, 2, new QTableWidgetItem(QString::number(proceso.tiempoTranscurrido / 1000.0)));
        fila++;
    }
}