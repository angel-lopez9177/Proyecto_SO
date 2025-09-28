#ifndef TABLAEJECUCION_H
#define TABLAEJECUCION_H

#include "TablaBase.h"
#include <optional>

class TablaEjecucion : public TablaBase {
        Q_OBJECT
        public:
                explicit TablaEjecucion(QWidget *tabla);
                void mostrarProceso(const Proceso& proceso, const QString& operacion);
                void actualizarTiempos(const Proceso& proceso);
                void limpiar();
        private:
                void eliminar(int fila);
                void popFront();
                void popBack();
};

#endif // TABLAEJECUCION_H