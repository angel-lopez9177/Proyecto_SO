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
    tablaResultados = new TablaResultados();

    this->setFocusPolicy(Qt::StrongFocus);
    this->setCentralWidget(this->ui->centralwidget);

    timer = new QTimer(this);
    timer->setInterval(TIEMPO_ACTUALIZACION);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEjecucion);
}

MainWindow::~MainWindow()
{
    delete tablaResultados; 
    delete ui;
}


void MainWindow::setProcesos(const QList<Proceso>& procesos)
{
    this->procesos = procesos;
}

void MainWindow::agregarProceso(){
    if (procesos.empty()) return;
    Proceso proceso = procesos.front();
    procesos.pop_front();

    proceso.tiempoLlegada = tiempoTotal;

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
        tablaResultados->actualizarTabla(procesosFinalizados);
        tablaResultados->show();
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

        if (this->procesoEnEjecucion.value().tiempoPrimerServicio == -1) {
            this->procesoEnEjecucion.value().tiempoPrimerServicio = tiempoTotal;
        }
        
        Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
        
        QString operacion = GestorOperaciones::generarOperacionMatematica(procesoEnEjecucion);
        
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
            terminarProcesoActual();
            ejecutarSiguienteProceso();
        }
    }else{
        ejecutarSiguienteProceso();
    }
}

void MainWindow::terminarProcesoActual(){
    Proceso procesoTerminado = this->procesoEnEjecucion.value();
    procesoTerminado.tiempoFinalizacion = tiempoTotal;
    procesosFinalizados.append(procesoTerminado);
    QString operacion = ui->Tabla_Ejecucion->item(1, 0)->text();
    QString resultado = GestorOperaciones::calcularResultado(procesoTerminado);
    procesosEnMemoria--;
    this->procesoEnEjecucion.reset();
    this->ui->Tabla_Ejecucion->limpiar();
    ui->Tabla_Terminados->agregarProceso(procesoTerminado, operacion, resultado);
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
        case Qt::Key_B:
            mostrarTablaResultados();
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

void MainWindow::mostrarTablaResultados(){
    pausar();
    tablaResultados->setTiempoGlobal(tiempoTotal);
    tablaResultados->actualizarTabla(procesosFinalizados, procesoEnEjecucion, procesosListos, procesosBloqueados, procesos);
    tablaResultados->show();
}

void MainWindow::error(){
    if (this->procesoEnEjecucion.has_value()){
        terminarProcesoActual();
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

