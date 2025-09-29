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
    std::queue<Proceso> procesosBloqueados;
    std::queue<Proceso> procesosFinalizados;
    std::optional<Proceso> procesoEnEjecucion;
    int procesosEnMemoria;
    bool ejecucionActiva;

    void agregarProceso();

    void ejecutarSiguienteProceso();

    void terminarProcesoActual(QString resultado);

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

};
#endif // MAINWINDOW_H