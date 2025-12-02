#ifndef TABLARESULTADOS_H
#define TABLARESULTADOS_H

#include <QWidget>
#include "Proceso.h"
#include <QList>
#include <deque>
#include <optional>

namespace Ui {
class TablaResultados;
}
class TablaResultados : public QWidget
{
    Q_OBJECT
    public:
        explicit TablaResultados(QWidget *parent = nullptr);
        ~TablaResultados();
        void actualizarTabla(const QList<Proceso>& procesosTerminados, 
            const std::optional<Proceso>& procesoEjecucion, 
            const std::deque<Proceso>& procesosListos, 
            const std::deque<Proceso>& procesosBloqueados, 
            const QList<Proceso>& procesosNuevos,
            const QList<Proceso>& procesosSuspendidos);
        void actualizarTabla(const QList<Proceso>& procesosTerminados);
        void agregarProceso(const Proceso& proceso, int i);
        void limpiar();
        void setTiempoGlobal(int tiempoGlobal) { this->tiempoGlobal = tiempoGlobal; }
    private:
        Ui::TablaResultados *ui;
        int tiempoGlobal;
};

#endif // TABLARESULTADOS_H