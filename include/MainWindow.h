#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Programa.h"
#include <iostream>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setProgramas(const std::vector<Programa>& programas);
    ~MainWindow();
    void comenzarEjecucion();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::vector<Programa> programas;
    std::vector<Programa> programasFinalizados;
    Programa programaEnEjecucion;
    int tiempoTranscurrido;
    int loteActual;
    int programasEjecutados;
    bool ejecucionActiva;

    void llenarTablaPendientes();
    void agregarAFinalizados(const Programa& programa);
    void ejecutarSiguientePrograma();
    void vaciarFilaPendientes(int fila);
    void subirFilasPendientes();
    QString generarOperacionMatematica(int num1, int num2, int op);
    float calcularResultado(const QString& operacion);

private slots:
    void actualizarEjecucion();

};
#endif // MAINWINDOW_H