#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <QList>
#include <optional>
#include "Proceso.h"



class GestorDatos
{
public:
    static QList<Proceso> obtener_procesos(int cantidad);

private:
    static Proceso generar_proceso();
    static int ID;
};

#endif