#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <vector>
#include <optional>
#include "Proceso.h"

class GestorDatos
{
public:
    static std::optional<std::vector<Proceso>> obtener_procesos(int cantidad);

private:
    static Proceso generar_proceso(int ID);
};

#endif