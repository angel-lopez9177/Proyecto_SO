#include "TablaBloqueados.h"

TablaBloqueados::TablaBloqueados(QWidget *tabla) : TablaBase(tabla) {}

void TablaBloqueados::agregar(const int fila, const Proceso& proceso){
    if (fila < 0 || fila > this->rowCount()) {
        return;
    }
    this->insertRow(fila);
    this->setItem(fila, 0, new QTableWidgetItem(QString::number(proceso.ID)));
    this->setItem(fila, 1, new QTableWidgetItem(QString::number(proceso.tiempoBloqueado / 1000.0, 'f', 2)));
}

void TablaBloqueados::actualizarTiempo(const int fila, const int tiempo) {
        this->item(fila, 1)->setText(QString::number(tiempo / 1000.0, 'f', 2));
}

void TablaBloqueados::pushBack(const Proceso& proceso) {
    int fila = this->rowCount();
    this->insertRow(fila);
    this->setItem(fila, 0, new QTableWidgetItem(QString::number(proceso.ID)));
    this->setItem(fila, 1, new QTableWidgetItem(QString::number(proceso.tiempoBloqueado / 1000.0, 'f', 2)));
}

void TablaBloqueados::pushFront(const Proceso& proceso) {
    this->insertRow(0);
    this->setItem(0, 0, new QTableWidgetItem(QString::number(proceso.ID)));
    this->setItem(0, 1, new QTableWidgetItem(QString::number(proceso.tiempoBloqueado / 1000.0, 'f', 2)));
}

