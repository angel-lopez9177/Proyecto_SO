#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VentanaDatos.h"
#include "GestorOperaciones.h"

#define MAX_PROCESOS_EN_MEMORIA 4
#define TIEMPO_ACTUALIZACION 50 // ms
#define TIEMPO_BLOQUEO 8000 // ms

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ejecucionActiva(false)
    , procesosEnMemoria(0)
    , tiempoTotal(0)
{
    ui->setupUi(this);

    procesoEnEjecucion.reset();

    this->setFocusPolicy(Qt::StrongFocus);
    this->setCentralWidget(this->ui->centralwidget);

    timer = new QTimer(this);
    timer->setInterval(TIEMPO_ACTUALIZACION);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEjecucion);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setProcesos(const std::list<Proceso>& procesos)
{
    this->procesos = procesos;
}

void MainWindow::agregarProceso(){
    if (procesos.empty()) return;
    Proceso proceso = procesos.front();
    procesos.pop_front();
    procesosListos.push_back(proceso);
    this->ui->Tabla_Listos->pushBack(proceso);
    procesosEnMemoria++;
}

void MainWindow::comenzarEjecucion(){
    
    ejecucionActiva = true;
    ejecutarSiguienteProceso();
    timer->start();
}

void MainWindow::ejecutarSiguienteProceso()
{
    if (procesos.empty() && procesosListos.empty() && procesosBloqueados.empty()){
        std::cout << "No hay más procesos para ejecutar." << std::endl;
        timer->stop();
        ejecucionActiva = false;
        this->procesoEnEjecucion.reset();
        this->ui->Tabla_Ejecucion->limpiar();
        return;
    }
    while (procesosEnMemoria < MAX_PROCESOS_EN_MEMORIA && !procesos.empty()){
        agregarProceso();
    }
    this->ui->Contador_Procesos->setText(QString::number(procesos.size()));
    if (!(procesosListos.empty())){
        this->procesoEnEjecucion = procesosListos.front();
        procesosListos.pop_front();
        this->ui->Tabla_Listos->popFront();
        
        Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
        
        QString operacion = generarOperacionMatematica(procesoEnEjecucion.numero1, procesoEnEjecucion.numero2, procesoEnEjecucion.indiceOperacion);
        
        ui->Tabla_Ejecucion->mostrarProceso(procesoEnEjecucion, operacion);
    }
}

void MainWindow::actualizarEjecucion()
{
    if (!ejecucionActiva) return;

    tiempoTotal += TIEMPO_ACTUALIZACION;
    ui->Contador_Tiempo->setText(QString::number(tiempoTotal / 1000.0, 'f', 2) + " s");

    if (!(procesosBloqueados.empty())){ 
        for(long unsigned int i = 0; i < procesosBloqueados.size(); i++){
            procesosBloqueados[i].tiempoBloqueado += TIEMPO_ACTUALIZACION;
            this->ui->Tabla_Bloqueados->actualizarTiempo(i, procesosBloqueados[i].tiempoBloqueado);
        }
        if (procesosBloqueados[0].tiempoBloqueado >= TIEMPO_BLOQUEO){
            procesosBloqueados[0].tiempoBloqueado = 0;
            procesosListos.push_back(procesosBloqueados[0]);
            this->ui->Tabla_Listos->pushBack(procesosBloqueados[0]);
            procesosBloqueados.pop_front();
            this->ui->Tabla_Bloqueados->popFront();
        }
    }
    if (this->procesoEnEjecucion.has_value()){
        this->procesoEnEjecucion.value().tiempoTranscurrido += TIEMPO_ACTUALIZACION;
        const Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
        
        ui->Tabla_Ejecucion->actualizarTiempos(procesoEnEjecucion);
        
        if (procesoEnEjecucion.tiempoTranscurrido >= procesoEnEjecucion.tiempoEstimado) {
            float r = calcularResultado(ui->Tabla_Ejecucion->item(1, 0)->text());
            QString resultado = QString::number(r);
            terminarProcesoActual(resultado);
            ejecutarSiguienteProceso();
        }
    }else{
        ejecutarSiguienteProceso();
    }
}

void MainWindow::terminarProcesoActual(QString resultado){
    Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
    QString operacion = ui->Tabla_Ejecucion->item(1, 0)->text();
    procesosEnMemoria--;
    this->procesoEnEjecucion.reset();
    this->ui->Tabla_Ejecucion->limpiar();
    ui->Tabla_Terminados->agregarProceso(procesoEnEjecucion, operacion, resultado);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_P:
            pausar();
            break;
        case Qt::Key_C:
            reanudar();
            break;
        case Qt::Key_E:
            interrupcion();
            break;
        case Qt::Key_W:
            error();
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::pausar() {
    timer->stop();
}

void MainWindow::reanudar() {
    timer->start();
}

void MainWindow::error(){
    if (this->procesoEnEjecucion.has_value()){
        QString resultado = QString("Error");
        terminarProcesoActual(resultado);
        ejecutarSiguienteProceso();
    }
    return;
}

void MainWindow::interrupcion(){
    if (this->procesoEnEjecucion.has_value()){
        Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
        this->ui->Tabla_Bloqueados->pushBack(procesoEnEjecucion);
        procesosBloqueados.push_back(procesoEnEjecucion);
        this->ui->Tabla_Ejecucion->limpiar();
        this->procesoEnEjecucion.reset();
        ejecutarSiguienteProceso();
    }
    return;
}

