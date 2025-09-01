#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <vector>
#include <optional>
#include "Programa.h"

class GestorDatos
{
public:
    static std::optional<std::vector<Programa>> obtener_programas(int cantidad);
};

#endif