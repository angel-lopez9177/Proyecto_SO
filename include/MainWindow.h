#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Declaración forward - para la interfaz generada
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;  // Puntero a tu interfaz generada
};

#endif // MAINWINDOW_H