#ifndef TABLABASE_H
#define TABLABASE_H

#include <QTableWidget>
#include "Proceso.h"

class TablaBase : public QTableWidget {
    Q_OBJECT
    public:
        explicit TablaBase(QWidget *parent = nullptr); 
        virtual ~TablaBase() = default;

        virtual void limpiar();
        virtual void eliminar(int fila);
        virtual void popBack();
        virtual void popFront();
};

#endif // TABLABASE_H