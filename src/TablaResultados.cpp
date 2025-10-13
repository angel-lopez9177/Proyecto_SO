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

void TablaResultados::actualizarTabla(const QList<Proceso>& procesosTerminados, const std::optional<Proceso>& procesoEjecucion, const std::deque<Proceso>& procesosListos, const std::deque<Proceso>& procesosBloqueados, const QList<Proceso>& procesosNuevos){
    limpiar();
    ui->Tabla_Resultados->setRowCount(procesosTerminados.size() + (procesoEjecucion.has_value() ? 1 : 0) + procesosListos.size() + procesosBloqueados.size() + procesosNuevos.size());
    int index = 0;
    for (int i = 0; i < procesosTerminados.size(); ++i) {
        const Proceso& p = procesosTerminados.at(i);
        agregarProceso(p, index++);
    }
    if (procesoEjecucion.has_value()){
        agregarProceso(procesoEjecucion.value(), index++);
    }
    for (size_t i = 0; i < procesosListos.size(); ++i) {
        const Proceso& p = procesosListos.at(i);
        agregarProceso(p, index++);
    }
    for (size_t i = 0; i < procesosBloqueados.size(); ++i) {
        const Proceso& p = procesosBloqueados.at(i);
        agregarProceso(p, index++);
    }
    for (int i = 0; i < procesosNuevos.size(); ++i) {
        const Proceso& p = procesosNuevos.at(i);
        agregarProceso(p, index++);
    }
}

void TablaResultados::actualizarTabla(const QList<Proceso>& procesosTerminados){
    limpiar();
    ui->Tabla_Resultados->setRowCount(procesosTerminados.size());
    int index = 0;
    for (int i = 0; i < procesosTerminados.size(); ++i) {
        const Proceso& p = procesosTerminados.at(i);
        agregarProceso(p, index++);
    }
}

void TablaResultados::agregarProceso(const Proceso& p, int i){
    int tiempoRetorno = p.tiempoFinalizacion - p.tiempoLlegada;
    int tiempoServicio = p.tiempoTranscurrido;
    int tiempoEspera = tiempoGlobal - p.tiempoLlegada - tiempoServicio;
    int tiempoRespuesta = (p.tiempoPrimerServicio != -1) ? (p.tiempoPrimerServicio - p.tiempoLlegada) : -1;
    int tiempoRestante = -1;
    if (p.tiempoFinalizacion != -1){
        tiempoRestante = 0;
    }else if(p.tiempoFinalizacion == -1 && p.tiempoLlegada != -1){
        tiempoRestante = p.tiempoEstimado - p.tiempoTranscurrido;
    }
    QString operacion = GestorOperaciones::generarOperacionMatematica(p);
    QString resultado = GestorOperaciones::calcularResultado(p);

    // --- Llenado de la Tabla ---
    ui->Tabla_Resultados->setItem(i, 0, new QTableWidgetItem(QString::number(p.ID)));
    ui->Tabla_Resultados->setItem(i, 1, new QTableWidgetItem(operacion));
    ui->Tabla_Resultados->setItem(i, 2, new QTableWidgetItem( (p.tiempoFinalizacion == -1) ? "N/A" : resultado));
    ui->Tabla_Resultados->setItem(i, 3, new QTableWidgetItem( (p.tiempoLlegada == -1) ? "N/A" : QString::number(p.tiempoLlegada / 1000.0, 'f', 2)));
    ui->Tabla_Resultados->setItem(i, 4, new QTableWidgetItem( (p.tiempoFinalizacion == -1) ? "N/A" : QString::number(p.tiempoFinalizacion / 1000.0, 'f', 2)));
    ui->Tabla_Resultados->setItem(i, 5, new QTableWidgetItem( (p.tiempoFinalizacion == -1) ? "N/A" : QString::number(tiempoRetorno / 1000.0, 'f', 2)));
    ui->Tabla_Resultados->setItem(i, 6, new QTableWidgetItem( (tiempoRespuesta == -1) ? "N/A" : QString::number(tiempoRespuesta / 1000.0, 'f', 2)));
    ui->Tabla_Resultados->setItem(i, 7, new QTableWidgetItem( (p.tiempoLlegada == -1) ? "N/A" : QString::number(tiempoEspera / 1000.0, 'f', 2)));
    ui->Tabla_Resultados->setItem(i, 8, new QTableWidgetItem( (p.tiempoLlegada == -1) ? "N/A" : QString::number(tiempoServicio / 1000.0, 'f', 2)));
    ui->Tabla_Resultados->setItem(i, 9, new QTableWidgetItem( (tiempoRestante == -1) ? "N/A" : QString::number(tiempoRestante / 1000.0, 'f', 2)));
    ui->Tabla_Resultados->setItem(i, 10, new QTableWidgetItem(QString::number(p.tiempoEstimado / 1000.0, 'f', 2)));
}