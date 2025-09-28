#ifndef TABLALISTOS_H
#define TABLALISTOS_H

#include "TablaBase.h"
#include <deque>

class TablaListos : public TablaBase {
        Q_OBJECT

        public:
                explicit TablaListos(QWidget *tabla);

                void actualizar(const std::deque<Proceso>& procesosListos);
        };
#endif // TABLALISTOS_H