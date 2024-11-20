#ifndef TABLA_PAGINA_H
#define TABLA_PAGINA_H

#include "pagina_virtual.h"
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <stdexcept>

class TablaPagina {
private:
    std::vector<PVirtual*>* tabla_paginas;
    std::queue<PVirtual*> fifoQueue;
    std::list<PVirtual*> lruList;
    std::unordered_map<int, std::list<PVirtual*>::iterator> lruMap;

    int indice_reloj;
    int tamano;
    int capacidad;
    int* keys;
    std::string algReemplazo;
    int funcion_hash(int); 

public:
    TablaPagina(std::string, int);
    PVirtual* insertarPagina(PVirtual*, const std::vector<int>&, int);
    PVirtual* eliminarPagina(int); // Eliminar duplicados
    PVirtual* obtenerPagina(int);  // Eliminar duplicados
    PVirtual* reemplazarPagina(PVirtual*, const std::vector<int>&, int);
    PVirtual* optimo(const std::vector<int>&, int);
    PVirtual* fifo();
    PVirtual* lru();
    PVirtual* lruReloj();
    void actualizarLRU(PVirtual*);
};

#endif
