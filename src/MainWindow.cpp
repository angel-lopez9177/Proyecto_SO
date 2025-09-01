#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VentanaDatos.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tiempoTranscurrido(0)
    , loteActual(0)
    , programasEjecutados(0)
    , ejecucionActiva(false)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(50); // 50 ms
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEjecucion);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setProgramas(const std::vector<Programa>& programas)
{
    this->programas = programas;
    llenarTablaPendientes();
    
    int totalProgramas = programas.size();
    int lotesCompletos = totalProgramas / 4;
    int programasEnUltimoLote = totalProgramas % 4;
    int lotesRestantes = programasEnUltimoLote > 0 ? lotesCompletos : lotesCompletos - 1;
    
    ui->Contador_Lotes->setText(QString::number(lotesRestantes));
}

void MainWindow::llenarTablaPendientes()
{
    for (int i = 0; i < 4; i++) {
        vaciarFilaPendientes(i);
    }
    
    int programasMostrar = std::min(4, static_cast<int>(programas.size()));
    
    for (int i = 0; i < programasMostrar; i++) {
        QTableWidgetItem *itemNombre = new QTableWidgetItem(programas[i].nombreProgramador);
        QTableWidgetItem *itemTiempo = new QTableWidgetItem(QString::number(programas[i].tiempoEstimado));
        
        ui->Tabla_Pendientes->setItem(i, 0, itemNombre);
        ui->Tabla_Pendientes->setItem(i, 1, itemTiempo);
    }
}

void MainWindow::vaciarFilaPendientes(int fila)
{
    ui->Tabla_Pendientes->setItem(fila, 0, new QTableWidgetItem(""));
    ui->Tabla_Pendientes->setItem(fila, 1, new QTableWidgetItem(""));
}

void MainWindow::subirFilasPendientes()
{
    for (int i = 0; i < 3; i++) {
        QTableWidgetItem *itemNombre = ui->Tabla_Pendientes->item(i + 1, 0);
        QTableWidgetItem *itemTiempo = ui->Tabla_Pendientes->item(i + 1, 1);
        
        if (itemNombre && itemTiempo) {
            ui->Tabla_Pendientes->setItem(i, 0, new QTableWidgetItem(itemNombre->text()));
            ui->Tabla_Pendientes->setItem(i, 1, new QTableWidgetItem(itemTiempo->text()));
        } else {
            vaciarFilaPendientes(i);
        }
    }
    vaciarFilaPendientes(3);
}

QString MainWindow::generarOperacionMatematica(int num1, int num2, int op)
{
    switch (op) {
    case VentanaDatos::SUMA: return QString("%1 + %2").arg(num1).arg(num2);
    case VentanaDatos::RESTA: return QString("%1 - %2").arg(num1).arg(num2);
    case VentanaDatos::MULTIPLICACION: return QString("%1 * %2").arg(num1).arg(num2);
    case VentanaDatos::DIVISION: return QString("%1 / %2").arg(num1).arg(num2);
    case VentanaDatos::MODULO: return QString("%1 % %2").arg(num1).arg(num2);
    case VentanaDatos::POTENCIA: return QString("%1 ^ %2").arg(num1).arg(num2);
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
    
    ejecutarSiguientePrograma();
    timer->start();
}

void MainWindow::ejecutarSiguientePrograma()
{
    if (programas.empty()) {
        timer->stop();
        ejecucionActiva = false;
        return;
    }
    
    // Tomar el primer programa de la lista
    programaEnEjecucion = programas.front();
    programas.erase(programas.begin());
    
    // Generar operación matemática
    QString operacion = generarOperacionMatematica(programaEnEjecucion.numero1, programaEnEjecucion.numero2, programaEnEjecucion.indiceOperacion);
    
    // Actualizar tabla de ejecución
    ui->Tabla_Ejecucion->item(0, 0)->setText(programaEnEjecucion.nombreProgramador);
    ui->Tabla_Ejecucion->item(1, 0)->setText(operacion);
    ui->Tabla_Ejecucion->item(2, 0)->setText(QString::number(programaEnEjecucion.tiempoEstimado));
    ui->Tabla_Ejecucion->item(3, 0)->setText(QString::number(++programasEjecutados));
    ui->Tabla_Ejecucion->item(4, 0)->setText("0");
    ui->Tabla_Ejecucion->item(5, 0)->setText(QString::number(programaEnEjecucion.tiempoEstimado));
    
    tiempoTranscurrido = 0;
    
    // Actualizar tabla de pendientes
    subirFilasPendientes();
    if (!programas.empty() && programas.size() >= 4) {
        // Llenar la última fila si hay más programas
        QTableWidgetItem *itemNombre = new QTableWidgetItem(programas[3].nombreProgramador);
        QTableWidgetItem *itemTiempo = new QTableWidgetItem(QString::number(programas[3].tiempoEstimado));
        ui->Tabla_Pendientes->setItem(3, 0, itemNombre);
        ui->Tabla_Pendientes->setItem(3, 1, itemTiempo);
    }
}

void MainWindow::actualizarEjecucion()
{
    if (!ejecucionActiva) return;
    
    tiempoTranscurrido += 50; // 50 ms
    
    // Actualizar tiempos
    int tiempoRestante = programaEnEjecucion.tiempoEstimado * 1000 - tiempoTranscurrido;
    ui->Tabla_Ejecucion->item(4, 0)->setText(QString::number(tiempoTranscurrido / 1000.0, 'f', 1));
    ui->Tabla_Ejecucion->item(5, 0)->setText(QString::number(tiempoRestante / 1000.0, 'f', 1));
    
    // Actualizar reloj global
    static int tiempoTotal = 0;
    tiempoTotal += 50;
    ui->Contador_Tiempo->setText(QString::number(tiempoTotal / 1000.0, 'f', 1) + " s");
    
    // Verificar si el programa terminó
    if (tiempoTranscurrido >= programaEnEjecucion.tiempoEstimado * 1000) {
        // Calcular resultado de la operación
        QString operacion = ui->Tabla_Ejecucion->item(1, 0)->text();
        int resultado = calcularResultado(operacion);
        
        // Agregar a finalizados
        agregarAFinalizados(programaEnEjecucion);
        
        // Ejecutar siguiente programa
        ejecutarSiguientePrograma();
    }
}

void MainWindow::agregarAFinalizados(const Programa& programa)
{
    int row = ui->Tabla_Terminados->rowCount();
    ui->Tabla_Terminados->insertRow(row);
    
    QString operacion = ui->Tabla_Ejecucion->item(1, 0)->text();
    float resultado = calcularResultado(operacion);
    
    ui->Tabla_Terminados->setItem(row, 0, new QTableWidgetItem(QString::number(programasEjecutados)));
    ui->Tabla_Terminados->setItem(row, 1, new QTableWidgetItem(operacion));
    ui->Tabla_Terminados->setItem(row, 2, new QTableWidgetItem(QString::number(resultado)));
}
