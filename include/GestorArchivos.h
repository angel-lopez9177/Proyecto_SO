#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <QString>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QCoreApplication>
#include "Proceso.h"

class GestorArchivos
{
public:
    static void inicializar(); 
    
    static void guardarProceso(const Proceso &p);
    
    static void borrarProceso(int id);

    static QString obtenerRutaBase();

private:
    static QString rutaCarpeta;
};

#endif // GESTORARCHIVOS_H