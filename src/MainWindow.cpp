#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VentanaDatos.h"
#include "GestorOperaciones.h"
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>

#define LABEL_CONTADOR_OK ui->Label_ContadorTerminadosOK
#define LABEL_CONTADOR_ERROR ui->Label_ContadorTerminadosError
#define LABEL_SIGUIENTE_ID ui->Label_SiguienteID
#define LABEL_SIGUIENTE_TAMANO ui->Label_SiguienteTamano

#define TIEMPO_ACTUALIZACION 200 // ms
#define TIEMPO_BLOQUEO 8000 // ms

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ejecucionActiva(false)
    , tiempoTotal(0)
    , tiempoQuantum(0)
    , quantum(4000)
    , contTerminadosOK(0)
    , contTerminadosError(0)
{
    ui->setupUi(this);

    procesoEnEjecucion.reset();

    gestorMemoria = new GestorMemoria();

    tablaPaginas = new TablaPaginas(this);

    if (ui->layoutMemoria) {
        ui->layoutMemoria->addWidget(tablaPaginas);
    } else {
        tablaPaginas->setParent(this->ui->centralwidget);
        tablaPaginas->setGeometry(50, 350, 700, 200); 
        tablaPaginas->show();
    }

    tablaResultados = new TablaResultados();

    this->setFocusPolicy(Qt::StrongFocus);
    
    timer = new QTimer(this);
    timer->setInterval(TIEMPO_ACTUALIZACION);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEjecucion);

    GestorArchivos::inicializar();
    retornoSuspendidoPendiente = false;
}

MainWindow::~MainWindow()
{
    delete gestorMemoria;
    delete tablaResultados; 
    delete ui;
}

void MainWindow::setProcesos(const QList<Proceso>& procesos)
{
    this->procesos = procesos;
    ui->Contador_Procesos->setText(QString::number(procesos.size()));
    actualizarLabelSiguiente();
}

void MainWindow::comenzarEjecucion(){
    ejecucionActiva = true;
    ejecutarSiguienteProceso();
    timer->start();
}

void MainWindow::intentarCargarProcesos() {

    if (retornoSuspendidoPendiente && !colaSuspendidos.empty()) {
        Proceso &suspendido = colaSuspendidos.first();
        
        if (gestorMemoria->hayEspacioDisponible(suspendido.cantidadPaginas)) {
            recuperarProcesoDeDisco();
            retornoSuspendidoPendiente = false;
            return;
        } 
        return; 
    }

    while (!procesos.empty()) {
        Proceso &candidato = procesos.first();

        if (gestorMemoria->hayEspacioDisponible(candidato.cantidadPaginas)) {

            Proceso nuevoListo = procesos.takeFirst();

            gestorMemoria->asignarMemoria(nuevoListo);
            
            nuevoListo.tiempoLlegada = tiempoTotal;

            procesosListos.push_back(nuevoListo);
        } else {
            break; 
        }
    }

    ui->Contador_Procesos->setText(QString::number(procesos.size()));
    actualizarLabelSiguiente();
}

void MainWindow::ejecutarSiguienteProceso()
{
    intentarCargarProcesos();

    if (procesos.empty() && procesosListos.empty() && procesosBloqueados.empty() && !procesoEnEjecucion.has_value() && colaSuspendidos.empty()){
        std::cout << "Fin de simulación." << std::endl;
        timer->stop();
        ejecucionActiva = false;
        this->procesoEnEjecucion.reset();
        this->ui->Tabla_Ejecucion->limpiar();

        tablaResultados->actualizarTabla(procesosFinalizados);
        tablaResultados->show();
        QMessageBox::information(this, "Terminado", "Simulación finalizada.");
        return;
    }

    if (!procesoEnEjecucion.has_value() && !procesosListos.empty()){
        this->procesoEnEjecucion = procesosListos.front();
        tiempoQuantum = 0;
        procesosListos.pop_front();
        
        if (this->procesoEnEjecucion.value().tiempoPrimerServicio == -1) {
            this->procesoEnEjecucion.value().tiempoPrimerServicio = tiempoTotal;
        }
        
        Proceso &proc = this->procesoEnEjecucion.value();
        QString operacion = GestorOperaciones::generarOperacionMatematica(proc);
        ui->Tabla_Ejecucion->mostrarProceso(proc, operacion);
    }
}

void MainWindow::actualizarEjecucion()
{
    if (!ejecucionActiva) return;

    tiempoTotal += TIEMPO_ACTUALIZACION;
    ui->Contador_Tiempo->setText(QString::number(tiempoTotal / 1000.0, 'f', 2) + " s");
    ui->Contador_Quantum->setText(QString::number(((tiempoQuantum*(-1)+quantum) / 1000.0), 'f', 2) + " s");

    if (!procesosBloqueados.empty()){ 
        
        int n = procesosBloqueados.size();
        
        for(int i=0; i<n; ++i) {
            procesosBloqueados[i].tiempoBloqueado += TIEMPO_ACTUALIZACION;
        }
        
        if (procesosBloqueados.front().tiempoBloqueado >= TIEMPO_BLOQUEO) {
            Proceso desbloqueado = procesosBloqueados.front();
            desbloqueado.tiempoBloqueado = 0;
            
            procesosListos.push_back(desbloqueado);
            procesosBloqueados.pop_front();
        }
    }

    if (this->procesoEnEjecucion.has_value()){
        this->procesoEnEjecucion.value().tiempoTranscurrido += TIEMPO_ACTUALIZACION;
        tiempoQuantum += TIEMPO_ACTUALIZACION; 
        bool procesoDebeCambiar = false;
        
        Proceso &procesoActual = this->procesoEnEjecucion.value();
        ui->Tabla_Ejecucion->actualizarTiempos(procesoActual);
        
        if (procesoActual.tiempoTranscurrido >= procesoActual.tiempoEstimado) {
            terminarProcesoActual(true);
            procesoDebeCambiar = true;
        }
        else if(tiempoQuantum >= quantum){
            reemplazarProcesoEjecucion();
            procesoDebeCambiar = true;
            tiempoQuantum = 0;
        }

        if (procesoDebeCambiar) ejecutarSiguienteProceso();

    } else {
        ejecutarSiguienteProceso();
    }
    
    int idEjecucion = procesoEnEjecucion.has_value() ? procesoEnEjecucion->ID : -1;

    tablaPaginas->actualizarMemorias(gestorMemoria, idEjecucion, procesosListos, procesosBloqueados);
}

void MainWindow::reemplazarProcesoEjecucion(){
    if (procesoEnEjecucion.has_value()){
        Proceso procesoAReemplazar = procesoEnEjecucion.value();

        procesosListos.push_back(procesoAReemplazar);

        quitarProcesoEjecucion();
    }
}

void MainWindow::terminarProcesoActual(bool exito){
    if (!procesoEnEjecucion.has_value()) return;

    Proceso procesoTerminado = this->procesoEnEjecucion.value();
    procesoTerminado.tiempoFinalizacion = tiempoTotal;

    QString operacion = ui->Tabla_Ejecucion->item(1, 0)->text();
    QString resultado;
    
    if (exito) {
        resultado = GestorOperaciones::calcularResultado(procesoTerminado);
        contTerminadosOK++;
        if (LABEL_CONTADOR_OK) LABEL_CONTADOR_OK->setText(QString::number(contTerminadosOK));
    } else {
        resultado = "ERROR";
        contTerminadosError++;
        if (LABEL_CONTADOR_ERROR) LABEL_CONTADOR_ERROR->setText(QString::number(contTerminadosError));
    }

    procesosFinalizados.append(procesoTerminado);

    gestorMemoria->liberarMemoria(procesoTerminado);

    this->procesoEnEjecucion.reset();
    this->ui->Tabla_Ejecucion->limpiar();

    intentarCargarProcesos();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_P: pausar(); break;
        case Qt::Key_C: reanudar(); break;
        case Qt::Key_E: interrupcion(); break;
        case Qt::Key_W: error(); break;
        case Qt::Key_B: mostrarTablaResultados(); break;
        case Qt::Key_N: nuevoProceso(); break;
        case Qt::Key_T: mostrarTablaPaginasSeparada(); break;
        case Qt::Key_S: suspenderProceso(); break;
        case Qt::Key_R: prepararRetornoSuspendido(); break;
        default: QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::pausar() { timer->stop(); }
void MainWindow::reanudar() { timer->start(); }

void MainWindow::mostrarTablaResultados(){
    pausar();
    tablaResultados->setTiempoGlobal(tiempoTotal);
    tablaResultados->actualizarTabla(procesosFinalizados, procesoEnEjecucion, procesosListos, procesosBloqueados, procesos);
    tablaResultados->show();
}

void MainWindow::mostrarTablaPaginasSeparada() {
    pausar();
    
    QDialog ventanaT(this);
    ventanaT.setWindowTitle("Tabla de Páginas y Marcos Libres");
    ventanaT.resize(1200, 600); // Un poco más ancha
    
    QHBoxLayout *mainLayout = new QHBoxLayout(&ventanaT);
    
    QVBoxLayout *layoutVisual = new QVBoxLayout();
    layoutVisual->addWidget(new QLabel("Mapa de Memoria (Marcos):"));
    layoutVisual->addWidget(tablaPaginas); 
    mainLayout->addLayout(layoutVisual, 2);

    QVBoxLayout *layoutTexto = new QVBoxLayout();
    QTextEdit *reporte = new QTextEdit();
    reporte->setReadOnly(true);
    reporte->setFont(QFont("Consolas", 10)); 
    
    QString texto;
    
    texto += "=== TABLAS DE PÁGINAS POR PROCESO ===\n\n";
    
    auto imprimirProceso = [&](const Proceso &p, QString estado) {
        texto += QString("Proceso ID: %1 (%2)\n").arg(p.ID).arg(estado);
        texto += QString("  Tamaño: %1 | Páginas: %2\n").arg(p.tamano).arg(p.cantidadPaginas);
        texto += "  Página  ->  Marco    [Espacio Usado]\n";
        texto += "  ------------------------------------\n";
        
        for(int i = 0; i < p.marcosAsignados.size(); ++i) {
            QString usoInfo = "5/5";
            if (i == p.marcosAsignados.size() - 1) {
                int ocupado = p.tamano % 5;
                if (ocupado == 0) ocupado = 5;
                
                int desperdicio = 5 - ocupado;
                
                usoInfo = QString("%1/5").arg(ocupado);
                
                if (desperdicio > 0) {
                    usoInfo += QString(" (Frag. Interna: %1)").arg(desperdicio);
                }
            }

            texto += QString("     %1    ->    %2       %3\n")
                        .arg(i, -2)
                        .arg(p.marcosAsignados[i], -2) 
                        .arg(usoInfo);
        }
        texto += "\n";
    };

    if (procesoEnEjecucion.has_value()) 
        imprimirProceso(procesoEnEjecucion.value(), "EJECUCIÓN");
        
    for(const auto &p : procesosListos) 
        imprimirProceso(p, "LISTO");
        
    for(const auto &p : procesosBloqueados) 
        imprimirProceso(p, "BLOQUEADO");

    // B) Marcos Libres
    texto += "=== MARCOS LIBRES ===\n";
    texto += "Marcos disponibles para nuevos procesos:\n[ ";
    
    int libresCount = 0;
    // Iteramos los 48 marcos. Usamos el gestorMemoria para ver si están libres.
    // Nota: gestorMemoria usa unidades (240). Marco i = unidad i*5.
    for(int i = 0; i < 48; ++i) { // 44 usuarios + 4 SO
        if (gestorMemoria->obtenerEstadoUnidad(i * 5) == -1) {
            texto += QString::number(i) + " ";
            libresCount++;
        }
    }
    texto += "]\n";
    texto += QString("Total Marcos Libres: %1 / 44\n").arg(libresCount); // Sin contar SO

    reporte->setText(texto);
    
    layoutTexto->addWidget(new QLabel("Detalle de Paginación:"));
    layoutTexto->addWidget(reporte);
    mainLayout->addLayout(layoutTexto, 1); // Factor de estiramiento 1

    // Mostrar
    ventanaT.exec();
    
    // Devolver widget a su lugar
    if (ui->layoutMemoria) {
        ui->layoutMemoria->addWidget(tablaPaginas);
    } else {
        tablaPaginas->setParent(this->ui->centralwidget);
        tablaPaginas->show();
    }
}

void MainWindow::error(){
    if (this->procesoEnEjecucion.has_value()){
        terminarProcesoActual(false);
        ejecutarSiguienteProceso();
    }
}

void MainWindow::quitarProcesoEjecucion(){
    if (this->procesoEnEjecucion.has_value()){
        this->ui->Tabla_Ejecucion->limpiar();
        this->procesoEnEjecucion.reset();
    }
}

void MainWindow::interrupcion(){
    if (this->procesoEnEjecucion.has_value()){
        Proceso procesoBloqueado = this->procesoEnEjecucion.value();
        procesoBloqueado.tiempoBloqueado = 0;
        
        procesosBloqueados.push_back(procesoBloqueado);
        
        quitarProcesoEjecucion();
        ejecutarSiguienteProceso();

    }
}

void MainWindow::nuevoProceso(){
    Proceso proceso = GestorDatos::generar_proceso();
    procesos.append(proceso);

    if (ejecucionActiva) {
        intentarCargarProcesos();
        if (!procesoEnEjecucion.has_value()){
            ejecutarSiguienteProceso();
        }
    } else {
        ui->Contador_Procesos->setText(QString::number(procesos.size()));
        actualizarLabelSiguiente();
    }
}

void MainWindow::actualizarLabelSiguiente() {
    if (procesos.isEmpty()) {
        if (LABEL_SIGUIENTE_ID) LABEL_SIGUIENTE_ID->setText("-");
        if (LABEL_SIGUIENTE_TAMANO) LABEL_SIGUIENTE_TAMANO->setText("-");
    } else {
        const Proceso &p = procesos.first();
        if (LABEL_SIGUIENTE_ID) LABEL_SIGUIENTE_ID->setText(QString::number(p.ID));
        if (LABEL_SIGUIENTE_TAMANO) LABEL_SIGUIENTE_TAMANO->setText(QString::number(p.tamano));
    }
}

void MainWindow::prepararRetornoSuspendido() {
    if (colaSuspendidos.empty()) return;

    retornoSuspendidoPendiente = true;
    intentarCargarProcesos();
    return;
}

void MainWindow::actualizarLabelsSuspendidos() {
    ui->Label_ContadorSuspendidos->setText(QString::number(colaSuspendidos.size()));

    if (!colaSuspendidos.empty()) {
        const Proceso &p = colaSuspendidos.first();
        ui->Label_ProximoSuspendidoID->setText(QString::number(p.ID));
        ui->Label_ProximoSuspendidoTamano->setText(QString::number(p.tamano));
    } else {
        ui->Label_ProximoSuspendidoID->setText("-");
        ui->Label_ProximoSuspendidoTamano->setText("-");
    }
}

void MainWindow::suspenderProceso() {
    if (procesosBloqueados.empty()) return;

    Proceso p = procesosBloqueados.front();
    procesosBloqueados.pop_front();
    
    gestorMemoria->liberarMemoria(p);

    GestorArchivos::guardarProceso(p);
    
    colaSuspendidos.append(p);
    actualizarLabelsSuspendidos();
    
    int idEjec = procesoEnEjecucion.has_value() ? procesoEnEjecucion->ID : -1;
    tablaPaginas->actualizarMemorias(gestorMemoria, idEjec, procesosListos, procesosBloqueados);
    
    intentarCargarProcesos();
}

void MainWindow::recuperarProcesoDeDisco() {
    if (colaSuspendidos.empty()) return;

    timer->stop();
    
    Proceso p = colaSuspendidos.takeFirst();

    GestorArchivos::borrarProceso(p.ID);
    
    p.tiempoBloqueado = 0;

    gestorMemoria->asignarMemoria(p);
    procesosListos.push_back(p);
    
    actualizarLabelsSuspendidos();

    int idEjec = procesoEnEjecucion.has_value() ? procesoEnEjecucion->ID : -1;
    tablaPaginas->actualizarMemorias(gestorMemoria, idEjec, procesosListos, procesosBloqueados);
    
    timer->start();
}