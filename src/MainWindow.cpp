#include "MainWindow.h"
#include "ui_MainWindow.h"  // Archivo generado por uic - NO lo modifiques

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;  // Liberar memoria
}