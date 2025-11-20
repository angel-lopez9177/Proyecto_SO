#ifndef GESTORMEMORIA_H
#define GESTORMEMORIA_H

#include <vector>
#include "Proceso.h"

class GestorMemoria {
public:
    GestorMemoria();

    bool hayEspacioDisponible(int cantidadPaginas);
    
    void asignarMemoria(Proceso &proceso);
    
    void liberarMemoria(Proceso &proceso);

    int obtenerEstadoUnidad(int index);

    int totalMarcos() const { return 48; }
    int tamanoMarco() const { return 5; }

private:
    std::vector<int> memoria; 
};

#endif