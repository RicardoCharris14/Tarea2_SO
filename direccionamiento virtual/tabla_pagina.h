#ifndef TABLA_PAGINA_H
#define TABLA_PAGINA_h

#include "pagina_virtual.h"
#include <string>
#include <vector>

class TablaPagina{
private:
    std::vector<PVirtual*>* tabla_paginas;
    int tamano;
    int capacidad;
    int* keys;
    std::string algReemplazo;
public:
    TablaPagina(std::string, int);
    void insertarPagina(PVirtual*);
    PVirtual* eliminarPagina(int);
    PVirtual* obtenerPagina(int);
    PVirtual* reemplazarPagina(PVirtual*);
private:
    int funcion_hash(int);
    PVirtual* optimo();
    PVirtual* fifo();
    PVirtual* lru();
    PVirtual* lruReloj();
};
#endif