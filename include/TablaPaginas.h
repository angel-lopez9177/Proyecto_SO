#ifndef TABLAPAGINAS_H
#define TABLAPAGINAS_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <deque>
#include "GestorMemoria.h"
#include "MarcoDelegate.h"

class TablaPaginas : public QWidget {
    Q_OBJECT
public:
    explicit TablaPaginas(QWidget *parent = nullptr);
    
    void actualizarMemorias(GestorMemoria *memoria, 
                            int idEjecucion, 
                            const std::deque<Proceso>& listos,
                            const std::deque<Proceso>& bloqueados);

private:
    QTableWidget *tabla;
    void configurarTabla();
    
    int determinarEstadoVisual(int idProceso, int idEjecucion, 
                            const std::deque<Proceso>& listos,
                            const std::deque<Proceso>& bloqueados);
};

#endif