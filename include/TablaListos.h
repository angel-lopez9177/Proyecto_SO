#ifndef TABLALISTOS_H
#define TABLALISTOS_H

#include "TablaBase.h"
#include "Proceso.h"
#include <deque>

class TablaListos : public TablaBase {
        Q_OBJECT

        public:
                explicit TablaListos(QWidget *tabla);

                void actualizar(const std::deque<Proceso>& procesosListos);
                void agregar(const int fila, const Proceso& proceso);
                void pushBack(const Proceso& proceso);
                void pushFront(const Proceso& proceso);
        };
#endif // TABLALISTOS_H