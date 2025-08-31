#include "VentanaDatos.h"
#include "ui_VentanaDatos.h"
#include <QMessageBox>

std::optional<Programa> VentanaDatos::resultadoStatico = std::nullopt;

VentanaDatos::VentanaDatos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VentanaDatos)
{
    ui->setupUi(this);

    connect(ui->Boton_Aceptar, &QPushButton::clicked, this, &VentanaDatos::boton_aceptar_clicked);

    connect(this, &VentanaDatos::closeEvent, [this]() {
        if (!resultadoStatico.has_value()) {
            throw std::runtime_error("");
        }
    });
}

VentanaDatos::~VentanaDatos()
{
    delete ui;
}

std::optional<Programa> VentanaDatos::obtener_datos()
{
    int argc = 0;
    char **argv = nullptr;
    QApplication* app = nullptr;
    if (!QApplication::instance()) {
        app = new QApplication(argc, argv);
    } else {
        app = qobject_cast<QApplication*>(QApplication::instance());
    }
    
    VentanaDatos ventana;
    ventana.show();

    resultadoStatico = std::nullopt;

    QEventLoop loop;
    QObject::connect(&ventana, &VentanaDatos::datosListos, &loop, &QEventLoop::quit);
    QObject::connect(&ventana, &VentanaDatos::usuarioCancelo, &loop, &QEventLoop::quit);
    loop.exec();
    
    return resultadoStatico;
}

void VentanaDatos::boton_aceptar_clicked()
{
    try {
        // Validar y obtener datos
        QString nombre = ui->Texto_Nombre->text();
        if (nombre.isEmpty()) {
            throw std::runtime_error("El nombre no puede estar vacío");
        }
        
        bool ok;
        int tiempoEstimado = ui->Tiempo->value();
        if (tiempoEstimado < 1) {
            throw std::runtime_error("Tiempo de llegada inválido");
        }
        
        int operacion = ui->Combo_Operacion->currentIndex();

        int valor1 = ui->Dato1->value();
        if (valor1 < 0) {
            throw std::runtime_error("Tiempo de ejecución inválido");
        }
        
        int valor2 = ui->Dato2->value();
        if (valor2 < 0) {
            throw std::runtime_error("Tiempo de ejecución inválido");
        }
        if (operacion == Operacion::DIVISION && valor2 == 0){
            throw std::runtime_error("No se permite division entre 0");
        }

        int ID = ui->ID->value();
        if (ID < 0) {
            throw std::runtime_error("Tiempo de ejecución inválido");
        }

        // Crear estructura Programa
        Programa programa;
        programa.nombreProgramador = nombre;
        programa.tiempoEstimado = tiempoEstimado;
        programa.indiceOperacion = operacion;
        programa.ID = ID;
        programa.numero1 = valor1;
        programa.numero2 = valor2;
        
        // Guardar resultado y cerrar
        resultadoStatico = programa;
        emit usuarioCancelo();
        
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
