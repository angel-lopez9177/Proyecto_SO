#ifndef TABLATERMINADOS_H
#define TABLATERMINADOS_H

#include "TablaBase.h"

class TablaTerminados : public TablaBase {
        Q_OBJECT
        public:
                explicit TablaTerminados(QWidget *tabla);

                void agregarProceso(const Proceso& proceso, const QString& operacion, const QString& resultado);
        };

#endif // TABLATERMINADOS_H