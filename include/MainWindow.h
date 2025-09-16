#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Proceso.h"
#include <iostream>
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

    void setProcesos(const std::vector<Proceso>& procesos);
    ~MainWindow();
    void comenzarEjecucion();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::vector<Proceso> procesos;
    std::vector<Proceso> procesosFinalizados;
    Proceso procesoEnEjecucion;
    int tiempoTranscurrido;
    int lotesRestantes;
    int loteActual;
    int totalProcesos;
    int procesosRestantes;
    bool ejecucionActiva;

    void llenarTablaPendientes();
    void agregarProcesoFinalizados(const Proceso& proceso, const QString& operacion, const QString& resultado);
    void ejecutarSiguienteProceso();
    void vaciarFilaPendientes(int fila);
    void subirFilasPendientes();
    void vaciarTablaEjecucion();
    void terminaProcesoActual();
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