#ifndef TABLARESULTADOS_H
#define TABLARESULTADOS_H

#include <QWidget>
#include "Proceso.h"
#include <QList>

namespace Ui {
class TablaResultados;
}
class TablaResultados : public QWidget
{
        Q_OBJECT
        public:
                explicit TablaResultados(QWidget *parent = nullptr);
                ~TablaResultados();

                void actualizarTabla(const QList<Proceso>& procesosTerminados);
                void limpiar();

        private:
                Ui::TablaResultados *ui;
};

#endif // TABLARESULTADOS_H