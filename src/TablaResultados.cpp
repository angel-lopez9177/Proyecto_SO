#include "TablaResultados.h"
#include "ui_TablaResultados.h"
#include "GestorOperaciones.h"


TablaResultados::TablaResultados(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TablaResultados)
{
    ui->setupUi(this);
}

TablaResultados::~TablaResultados()
{
    delete ui;
}

void TablaResultados::limpiar(){
    ui->Tabla_Resultados->setRowCount(0);
}

void TablaResultados::actualizarTabla(const QList<Proceso>& procesosTerminados){
    limpiar();
    ui->Tabla_Resultados->setRowCount(procesosTerminados.size());

    for (int i = 0; i < procesosTerminados.size(); ++i) {
        const Proceso& p = procesosTerminados.at(i);

        int tiempoRetorno = p.tiempoFinalizacion - p.tiempoLlegada;
        int tiempoServicio = p.tiempoTranscurrido;
        int tiempoEspera = tiempoRetorno - tiempoServicio;
        int tiempoRespuesta = (p.tiempoPrimerServicio != -1) ? (p.tiempoPrimerServicio - p.tiempoLlegada) : -1;

        QString operacion = GestorOperaciones::generarOperacionMatematica(p);
        QString resultado = GestorOperaciones::calcularResultado(p);

        // --- Llenado de la Tabla ---
        ui->Tabla_Resultados->setItem(i, 0, new QTableWidgetItem(QString::number(p.ID)));
        ui->Tabla_Resultados->setItem(i, 1, new QTableWidgetItem(operacion));
        ui->Tabla_Resultados->setItem(i, 2, new QTableWidgetItem(resultado));
        ui->Tabla_Resultados->setItem(i, 3, new QTableWidgetItem(QString::number(p.tiempoLlegada / 1000.0, 'f', 2)));
        ui->Tabla_Resultados->setItem(i, 4, new QTableWidgetItem( (p.tiempoFinalizacion == -1) ? "N/A" : QString::number(p.tiempoFinalizacion / 1000.0, 'f', 2)));
        ui->Tabla_Resultados->setItem(i, 5, new QTableWidgetItem( (p.tiempoFinalizacion == -1) ? "N/A" : QString::number(tiempoRetorno / 1000.0, 'f', 2)));
        ui->Tabla_Resultados->setItem(i, 6, new QTableWidgetItem( (tiempoRespuesta == -1) ? "N/A" : QString::number(tiempoRespuesta / 1000.0, 'f', 2)));
        ui->Tabla_Resultados->setItem(i, 7, new QTableWidgetItem( (p.tiempoFinalizacion == -1) ? "N/A" : QString::number(tiempoEspera / 1000.0, 'f', 2)));
        ui->Tabla_Resultados->setItem(i, 8, new QTableWidgetItem(QString::number(tiempoServicio / 1000.0, 'f', 2)));
        ui->Tabla_Resultados->setItem(i, 9, new QTableWidgetItem(QString::number(p.tiempoEstimado / 1000.0, 'f', 2)));
    }
}