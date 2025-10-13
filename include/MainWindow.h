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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setProcesos(const QList<Proceso>& procesos);
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

    void agregarProceso();

    void ejecutarSiguienteProceso();

    void terminarProcesoActual();

    void pausar();
    void reanudar();
    void error();
    void interrupcion();
    void mostrarTablaResultados();

private slots:
    void actualizarEjecucion();

protected:
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // MAINWINDOW_H