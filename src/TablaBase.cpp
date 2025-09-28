#include "TablaBase.h"

TablaBase::TablaBase(QWidget *parent) : QTableWidget(parent) {
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TablaBase::limpiar() {
    this->clearContents();
    this->setRowCount(0);
}