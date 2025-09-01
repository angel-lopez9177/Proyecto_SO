#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VentanaDatos.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tiempoTranscurrido(0)
    , lotesRestantes(0)
    , totalProgramas(0)
    , ejecucionActiva(false)
    , programasRestantes(0)
{
    ui->setupUi(this);

    ui->Tabla_Terminados->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Tabla_Pendientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Tabla_Ejecucion->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
    
    this->totalProgramas = programas.size();
    this->lotesRestantes = (totalProgramas-1) / 4;
    this->lotesRestantes++;
    
    ui->Contador_Lotes->setText(QString::number(lotesRestantes));
}

void MainWindow::llenarTablaPendientes()
{
    for (int i = 0; i < 4; i++) {
        vaciarFilaPendientes(i);
    }

    lotesRestantes--;
    this->ui->Contador_Lotes->setText(QString::number(lotesRestantes));
    this->programasRestantes = std::min(4, static_cast<int>(programas.size()));
    
    for (int i = 0; i < programasRestantes; i++) {
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
        vaciarTablaEjecucion();
        return;
    }else{
        if (lotesRestantes>0 && programasRestantes==0){
            llenarTablaPendientes();
            std::cout<<"RellenarTabla"<<std::endl;
        }
    }
    std::cout<<programasRestantes<<std::endl;

    programaEnEjecucion = programas.front();
    programas.erase(programas.begin());
    programasRestantes--;
    
    QString operacion = generarOperacionMatematica(programaEnEjecucion.numero1, programaEnEjecucion.numero2, programaEnEjecucion.indiceOperacion);
    
    ui->Tabla_Ejecucion->item(0, 0)->setText(programaEnEjecucion.nombreProgramador);
    ui->Tabla_Ejecucion->item(1, 0)->setText(operacion);
    ui->Tabla_Ejecucion->item(2, 0)->setText(QString::number(programaEnEjecucion.tiempoEstimado));
    ui->Tabla_Ejecucion->item(3, 0)->setText(QString::number(programaEnEjecucion.ID));
    ui->Tabla_Ejecucion->item(4, 0)->setText("0");
    ui->Tabla_Ejecucion->item(5, 0)->setText(QString::number(programaEnEjecucion.tiempoEstimado));

    tiempoTranscurrido = 0;
    
    subirFilasPendientes();
}

void MainWindow::actualizarEjecucion()
{
    if (!ejecucionActiva) return;
    
    tiempoTranscurrido += 50;
    
    int tiempoRestante = programaEnEjecucion.tiempoEstimado * 1000 - tiempoTranscurrido;
    ui->Tabla_Ejecucion->item(4, 0)->setText(QString::number(tiempoTranscurrido / 1000.0, 'f', 1));
    ui->Tabla_Ejecucion->item(5, 0)->setText(QString::number(tiempoRestante / 1000.0, 'f', 1));
    
    static int tiempoTotal = 0;
    tiempoTotal += 50;
    ui->Contador_Tiempo->setText(QString::number(tiempoTotal / 1000.0, 'f', 1) + " s");
    
    if (tiempoTranscurrido >= programaEnEjecucion.tiempoEstimado * 1000) {
        agregarAFinalizados(programaEnEjecucion);
        ejecutarSiguientePrograma();
    }
}

void MainWindow::vaciarTablaEjecucion(){
    for(int i = 0; i<ui->Tabla_Ejecucion->rowCount();i++)
    ui->Tabla_Ejecucion->setItem(i, 0, new QTableWidgetItem(""));
}

void MainWindow::agregarAFinalizados(const Programa& programa)
{
    int row = ui->Tabla_Terminados->rowCount();
    ui->Tabla_Terminados->insertRow(row);
    
    QString operacion = ui->Tabla_Ejecucion->item(1, 0)->text();
    float resultado = calcularResultado(operacion);
    
    ui->Tabla_Terminados->setItem(row, 0, new QTableWidgetItem(QString::number(programa.ID)));
    ui->Tabla_Terminados->setItem(row, 1, new QTableWidgetItem(operacion));
    ui->Tabla_Terminados->setItem(row, 2, new QTableWidgetItem(QString::number(resultado)));

}
