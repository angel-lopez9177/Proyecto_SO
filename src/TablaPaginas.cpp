#include "TablaPaginas.h"
#include <QHeaderView>

TablaPaginas::TablaPaginas(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    tabla = new QTableWidget(this);
    layout->addWidget(tabla);
    layout->setContentsMargins(0,0,0,0);
    
    configurarTabla();
}

void TablaPaginas::configurarTabla() {

    tabla->setRowCount(8);
    tabla->setColumnCount(12);

    tabla->verticalHeader()->setVisible(false);
    tabla->horizontalHeader()->setVisible(false);

    tabla->setItemDelegate(new MarcoDelegate(tabla));
    
    for(int c = 0; c < 12; ++c) {
        if (c % 2 == 0) {
            tabla->setColumnWidth(c, 60);
        } else {
            tabla->setColumnWidth(c, 25); 
            tabla->setItemDelegateForColumn(c, nullptr); 
        }
    }

    int marcoID = 0;
    
    for(int i = 0; i < 8; ++i) { 
        for(int j = 0; j < 6; ++j) { 
            int colMarco = j * 2;
            int colEtiqueta = j * 2 + 1;

            tabla->setItem(i, colMarco, new QTableWidgetItem());
            
            QTableWidgetItem *lbl = new QTableWidgetItem(QString::number(marcoID));
            lbl->setTextAlignment(Qt::AlignCenter);
            lbl->setFlags(Qt::ItemIsEnabled); 
            
            lbl->setBackground(QColor(200, 200, 200));
            lbl->setForeground(Qt::black);            

            tabla->setItem(i, colEtiqueta, lbl);
            
            marcoID++;
        }
    }
}

void TablaPaginas::actualizarMemorias(GestorMemoria *memoria, 
                                    int idEjecucion, 
                                    const std::deque<Proceso>& listos,
                                    const std::deque<Proceso>& bloqueados) {
    int marcoIndex = 0;
    
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 6; ++j) {
            int colMarco = j * 2;

            QList<QVariant> estadosUnidades;
            int inicioUnidad = marcoIndex * 5;
            
            for(int u = 0; u < 5; ++u) {
                int idProc = memoria->obtenerEstadoUnidad(inicioUnidad + u);
                
                if (idProc == -1) estadosUnidades << -1; 
                else if (idProc == -2) estadosUnidades << -2; 
                else {

                    int estadoVis = determinarEstadoVisual(idProc, idEjecucion, listos, bloqueados);
                    estadosUnidades << estadoVis;
                }
            }

            tabla->item(i, colMarco)->setData(Qt::UserRole, estadosUnidades);

            int idRepresentativo = memoria->obtenerEstadoUnidad(inicioUnidad);
            if(idRepresentativo > 0)
                tabla->item(i, colMarco)->setText(QString::number(idRepresentativo));
            else if (idRepresentativo == -2)
                tabla->item(i, colMarco)->setText("SO");
            else
                tabla->item(i, colMarco)->setText("");

            marcoIndex++;
        }
    }

    tabla->viewport()->update();
}

int TablaPaginas::determinarEstadoVisual(int idProceso, int idEjecucion, 
                                        const std::deque<Proceso>& listos,
                                        const std::deque<Proceso>& bloqueados) {
    if (idProceso == idEjecucion) return 2;
    for(const auto& p : bloqueados) {
        if (p.ID == idProceso) return 3;
    }

    return 1;
}