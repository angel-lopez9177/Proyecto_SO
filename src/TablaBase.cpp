#include "TablaBase.h"

TablaBase::TablaBase(QWidget *parent) : QTableWidget(parent) {
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TablaBase::limpiar() {
    this->clearContents();
    this->setRowCount(0);
}


void TablaBase::eliminar(int fila){
    if (fila < 0 || fila >= this->rowCount()) {
        return; // Índice fuera de rango
    }
    this->removeRow(fila);
}

void TablaBase::popBack() {
    if (this->rowCount() > 0) {
        this->removeRow(this->rowCount() - 1);
    }
}

void TablaBase::popFront() {
    if (this->rowCount() > 0) {
        this->removeRow(0);
    }
}
