#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <QList>
#include <optional>
#include "Proceso.h"



class GestorDatos
{
public:
    static QList<Proceso> obtener_procesos(int cantidad);
    static Proceso generar_proceso();

private:
    static int ID;
};

#endif