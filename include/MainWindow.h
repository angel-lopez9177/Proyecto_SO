#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Programa.h"
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
    int lotesRestantes;
    int loteActual;
    int totalProgramas;
    int programasRestantes;
    bool ejecucionActiva;

    void llenarTablaPendientes();
    void agregarAFinalizados(const Programa& programa, const QString& operacion, const QString& resultado);
    void ejecutarSiguientePrograma();
    void vaciarFilaPendientes(int fila);
    void subirFilasPendientes();
    void vaciarTablaEjecucion();
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