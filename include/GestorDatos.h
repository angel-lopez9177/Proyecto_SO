#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <list>
#include <optional>
#include "Proceso.h"



class GestorDatos
{
public:
    static std::list<Proceso> obtener_procesos(int cantidad);

private:
    static Proceso generar_proceso(int ID);
};

#endif