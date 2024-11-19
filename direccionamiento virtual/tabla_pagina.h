#ifndef TABLA_PAGINA_H
#define TABLA_PAGINA_h

#include "pagina_virtual.h"
#include <string>
#include <queue> // LIFO 
#include <vector>

class TablaPagina{
private:
    std::vector<PVirtual*>* tabla_paginas;
    std::queue<PVirtual*> fifoQueue;
    int tamano;
    int capacidad;
    int* keys;
    std::string algReemplazo;
public:
    TablaPagina(std::string, int);
    PVirtual* insertarPagina(PVirtual*);
    PVirtual* eliminarPagina(int);
    PVirtual* obtenerPagina(int);
    
private:
    PVirtual* reemplazarPagina(PVirtual*);
    int funcion_hash(int);
    PVirtual* optimo();
    PVirtual* fifo();
    PVirtual* lru();
    PVirtual* lruReloj();
};
#endif