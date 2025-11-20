#include "GestorMemoria.h"
#include <cmath>

GestorMemoria::GestorMemoria() {
    memoria.resize(240, -1);
    for(int i = 220; i < 240; ++i) {
        memoria[i] = -2;
    }
}

bool GestorMemoria::hayEspacioDisponible(int cantidadPaginas) {
    int marcosLibres = 0;
    for(int i = 0; i < 48; ++i) {
        if (memoria[i * 5] == -1) {
            marcosLibres++;
        }
    }
    return marcosLibres >= cantidadPaginas;
}

void GestorMemoria::asignarMemoria(Proceso &proceso) {
    int paginasAsignadas = 0;
    int tamanoRestante = proceso.tamano;
    
    for(int i = 0; i < 48 && paginasAsignadas < proceso.cantidadPaginas; ++i) {
        if (memoria[i * 5] == -1) {
            int inicio = i * 5;
            proceso.marcosAsignados.append(i);

            int aLlenar = (tamanoRestante >= 5) ? 5 : tamanoRestante;
            
            for(int k = 0; k < aLlenar; ++k) {
                memoria[inicio + k] = proceso.ID;
            }
            
            tamanoRestante -= aLlenar;
            paginasAsignadas++;
        }
    }
}

void GestorMemoria::liberarMemoria(Proceso &proceso) {
    for(int marco : proceso.marcosAsignados) {
        int inicio = marco * 5;
        for(int k = 0; k < 5; ++k) {
            memoria[inicio + k] = -1;
        }
    }
    proceso.marcosAsignados.clear();
}

int GestorMemoria::obtenerEstadoUnidad(int index) {
    if(index < 0 || index >= 240) return -1;
    return memoria[index];
}