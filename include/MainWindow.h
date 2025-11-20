#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Proceso.h"
#include <iostream>
#include <deque>
#include <QList>
#include <QKeyEvent>
#include "TablaResultados.h"
#include "GestorDatos.h"
#include "TablaPaginas.h"
#include "GestorMemoria.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setProcesos(const QList<Proceso>& procesos);
    void setQuantum(int Q) {quantum = Q*1000; return;}
    ~MainWindow();
    void comenzarEjecucion();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    TablaResultados* tablaResultados;
    QList<Proceso> procesos;
    std::deque<Proceso> procesosListos;
    std::deque<Proceso> procesosBloqueados;
    QList<Proceso> procesosFinalizados;
    std::optional<Proceso> procesoEnEjecucion;
    int procesosEnMemoria;
    bool ejecucionActiva;
    int tiempoTotal;
    int tiempoQuantum;
    int quantum;
    int contTerminadosOK;
    int contTerminadosError;

    GestorMemoria *gestorMemoria;
    TablaPaginas *tablaPaginas;

    void agregarProceso();

    void ejecutarSiguienteProceso();
    void quitarProcesoEjecucion();
    void reemplazarProcesoEjecucion();

    void terminarProcesoActual(bool exito);

    void pausar();
    void reanudar();
    void error();
    void interrupcion();
    void mostrarTablaResultados();
    void nuevoProceso();

    void mostrarTablaPaginasSeparada();
    void intentarCargarProcesos();
    void actualizarLabelSiguiente();

private slots:
    void actualizarEjecucion();


protected:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // MAINWINDOW_H