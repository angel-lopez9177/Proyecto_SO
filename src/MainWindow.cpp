#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VentanaDatos.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , lotesRestantes(0)
    , totalLotes(0)
    , ejecucionActiva(false)
{
    ui->setupUi(this);

    procesoEnEjecucion.reset();

    this->setFocusPolicy(Qt::StrongFocus);
    this->setCentralWidget(this->ui->centralwidget);
    this->ui->centralwidget->installEventFilter(this);

    timer = new QTimer(this);
    timer->setInterval(50); // 50 ms
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEjecucion);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setProcesos(const std::list<Proceso>& procesos)
{
    this->procesos = procesos;
    int totalProcesos = procesos.size();
    this->totalLotes = ((totalProcesos-1) / 4) + 1;
    this->lotesRestantes = this->totalLotes;
    
    ui->Contador_Procesos->setText(QString::number(lotesRestantes));
}


void MainWindow::llenarProcesosListos(){
    int elementosRestantes = static_cast<int>(procesos.size());
    for(int i = 0; i<std::min(4, elementosRestantes); i++){
        procesosListos.push_back(procesos.front());
        procesos.pop_front();
    }
}

QString MainWindow::generarOperacionMatematica(int num1, int num2, int op)
{
    switch (op) {
    case Proceso::SUMA: return QString("%1 + %2").arg(num1).arg(num2);
    case Proceso::RESTA: return QString("%1 - %2").arg(num1).arg(num2);
    case Proceso::MULTIPLICACION: return QString("%1 * %2").arg(num1).arg(num2);
    case Proceso::DIVISION: return QString("%1 / %2").arg(num1).arg(num2);
    case Proceso::MODULO: return QString("%1 % %2").arg(num1).arg(num2);
    case Proceso::POTENCIA: return QString("%1 ^ %2").arg(num1).arg(num2);
    default: return QString("%1 + %2").arg(num1).arg(num2);
    }
}

float MainWindow::calcularResultado(const QString& operacion)
{
    if (operacion.contains('+')) {
        return operacion.split('+')[0].toInt() + operacion.split('+')[1].toInt();
    } else if (operacion.contains('-')) {
        return operacion.split('-')[0].toInt() - operacion.split('-')[1].toInt();
    } else if (operacion.contains('*')) {
        return operacion.split('*')[0].toInt() * operacion.split('*')[1].toInt();
    } else if (operacion.contains('/')) {
        return operacion.split('/')[0].toFloat() / operacion.split('/')[1].toFloat();
    } else if (operacion.contains('^')) {
        return pow(operacion.split('^')[0].toInt(), operacion.split('^')[1].toInt());
    } else if (operacion.contains('%')) {
        return operacion.split('%')[0].toInt() % operacion.split('%')[1].toInt();
    }
    return 0;
}

void MainWindow::comenzarEjecucion(){
    
    ejecucionActiva = true;
    ejecutarSiguienteProceso();
    timer->start();
}

void MainWindow::ejecutarSiguienteProceso()
{
    if (procesos.empty() && procesosListos.empty()) {
        timer->stop();
        ejecucionActiva = false;
        this->procesoEnEjecucion.reset();
        this->ui->Tabla_Ejecucion->limpiar();
        return;
    }
    if (lotesRestantes>0 && procesosListos.empty()){
        llenarProcesosListos();
        this->ui->Tabla_Listos->actualizar(procesosListos);
        lotesRestantes--;
        this->ui->Contador_Procesos->setText(QString::number(lotesRestantes));
    }

    this->procesoEnEjecucion = procesosListos.front();
    procesosListos.pop_front();
    this->ui->Tabla_Listos->popFront();
    
    Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
    
    QString operacion = generarOperacionMatematica(procesoEnEjecucion.numero1, procesoEnEjecucion.numero2, procesoEnEjecucion.indiceOperacion);
    
    ui->Tabla_Ejecucion->mostrarProceso(procesoEnEjecucion, operacion);
}

void MainWindow::actualizarEjecucion()
{
    if (!ejecucionActiva) return;

    this->procesoEnEjecucion.value().tiempoTranscurrido += 50;
    const Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
    
    ui->Tabla_Ejecucion->actualizarTiempos(procesoEnEjecucion);
    
    static int tiempoTotal = 0;
    tiempoTotal += 50;

    ui->Contador_Tiempo->setText(QString::number(tiempoTotal / 1000.0, 'f', 2) + " s");
    
    if (procesoEnEjecucion.tiempoTranscurrido >= procesoEnEjecucion.tiempoEstimado * 1000) {
        terminarProcesoActual();
        ejecutarSiguienteProceso();
    }
}

void MainWindow::terminarProcesoActual(){
    Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
    QString operacion = ui->Tabla_Ejecucion->item(1, 0)->text();
    float r = calcularResultado(operacion);
    QString resultado = QString::number(r);
    ui->Tabla_Terminados->agregarProceso(procesoEnEjecucion, operacion, resultado, totalLotes - lotesRestantes);
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
        Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
        QString operacion = ui->Tabla_Ejecucion->item(1, 0)->text();
        QString resultado = QString("Error");
        ui->Tabla_Terminados->agregarProceso(procesoEnEjecucion, operacion, resultado, totalLotes - lotesRestantes);
        ejecutarSiguienteProceso();
    }
    return;
}

void MainWindow::interrupcion(){
    if (this->procesoEnEjecucion.has_value()){
        Proceso procesoEnEjecucion = this->procesoEnEjecucion.value();
        this->ui->Tabla_Listos->pushBack(procesoEnEjecucion);
        procesosListos.push_back(procesoEnEjecucion);
        ejecutarSiguienteProceso();
    }
    return;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_P) {
            qDebug() << "En el central widget";
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}