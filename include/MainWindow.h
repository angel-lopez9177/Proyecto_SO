#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Proceso.h"
#include <iostream>
#include <queue>
#include <math.h>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setProcesos(const std::list<Proceso>& procesos);
    ~MainWindow();
    void comenzarEjecucion();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::list<Proceso> procesos;
    std::deque<Proceso> procesosListos;
    std::queue<Proceso> procesosFinalizados;
    std::optional<Proceso> procesoEnEjecucion;
    int tiempoTranscurrido;
    int lotesRestantes;
    int totalLotes;
    bool ejecucionActiva;

    void llenarTablaPendientes();
    void llenarFilaPendientes(int i, Proceso proceso);
    void llenarProcesosListos();
    void vaciarFilaPendientes(int fila);
    void subirFilasPendientes();

    void ejecutarSiguienteProceso();
    void vaciarTablaEjecucion();

    void agregarProcesoFinalizados(const Proceso& proceso, const QString& operacion, const QString& resultado);
    void terminarProcesoActual();

    QString generarOperacionMatematica(int num1, int num2, int op);
    float calcularResultado(const QString& operacion);

    void pausar();
    void reanudar();
    void error();
    void interrupcion();

private slots:
    void actualizarEjecucion();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

};
#endif // MAINWINDOW_H