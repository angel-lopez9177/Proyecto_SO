#ifndef TABLABLOQUEADOS_H
#define TABLABLOQUEADOS_H

#include "TablaBase.h"

class TablaBloqueados : public TablaBase {
        Q_OBJECT

        public:
                explicit TablaBloqueados(QWidget *tabla);

                void agregar(const int fila, const Proceso& proceso);
                void pushBack(const Proceso& proceso);
                void pushFront(const Proceso& proceso);
        };
#endif // TABLABLOQUEADOS_H