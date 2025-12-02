#include "GestorArchivos.h"
#include <QJsonArray>

QString GestorArchivos::rutaCarpeta = "";

void GestorArchivos::inicializar()
{
    QString path = QCoreApplication::applicationDirPath();
    
    int index = path.indexOf("/out/build");
    
    if (index != -1) {
        path = path.left(index);
    }
    
    rutaCarpeta = path + "/suspendidos";
    
    QDir dir(rutaCarpeta);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QFile file(rutaCarpeta + "/suspendidos.json");
    if (file.exists()) {
        file.remove();
    }
}

void GestorArchivos::guardarProceso(const Proceso &p)
{
    if (rutaCarpeta.isEmpty()) inicializar();

    QString rutaArchivo = rutaCarpeta + "/suspendidos.json";
    QJsonArray arrayProcesos;
    QFile fileLectura(rutaArchivo);
    
    if (fileLectura.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(fileLectura.readAll());
        arrayProcesos = doc.array();
        fileLectura.close();
    }

    QJsonObject json;
    json["ID"] = p.ID;
    json["tamano"] = p.tamano;
    json["cantidadPaginas"] = p.cantidadPaginas;
    json["tiempoEstimado"] = p.tiempoEstimado;
    json["tiempoTranscurrido"] = p.tiempoTranscurrido;
    json["tiempoLlegada"] = p.tiempoLlegada;
    json["tiempoBloqueado"] = p.tiempoBloqueado;
    json["numero1"] = p.numero1;
    json["numero2"] = p.numero2;
    json["indiceOperacion"] = p.indiceOperacion;
    json["tiempoPrimerServicio"] = p.tiempoPrimerServicio;

    arrayProcesos.append(json);

    QFile fileEscritura(rutaArchivo);
    if (fileEscritura.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(arrayProcesos);
        fileEscritura.write(doc.toJson());
        fileEscritura.close();
    }
}

void GestorArchivos::borrarProceso(int id)
{
    if (rutaCarpeta.isEmpty()) return;
    
    QString rutaArchivo = rutaCarpeta + "/suspendidos.json";
    QFile file(rutaArchivo);
    QJsonArray arrayProcesos;

    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        arrayProcesos = doc.array();
        file.close();
    } else {
        return;
    }

    for(int i = 0; i < arrayProcesos.size(); ++i) {
        QJsonObject obj = arrayProcesos[i].toObject();
        if (obj["ID"].toInt() == id) {
            arrayProcesos.removeAt(i);
            break; 
        }
    }

    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(arrayProcesos);
        file.write(doc.toJson());
        file.close();
    }
}

QString GestorArchivos::obtenerRutaBase() {
    return rutaCarpeta;
}