#include "tabla_pagina.h"

TablaPagina::TablaPagina(std::string algReemplazo, int capacidad){
    tabla_paginas = new std::vector<PVirtual*>(capacidad, nullptr);
    this->capacidad = capacidad;
    tamano = 0;
    keys = (int*)malloc(sizeof(int)*capacidad);
    this->algReemplazo = algReemplazo;
}
void TablaPagina::insertarPagina(PVirtual* pVirtual){
    if (tamano == capacidad){
        return;
    }
    int index = funcion_hash(pVirtual->obtenerPageNumber());
    if ((*tabla_paginas)[index] != nullptr){
        PVirtual* aux = (*tabla_paginas)[index];
        while(aux->next() != nullptr){
            aux = aux->next();
        }
        aux->setNext(pVirtual);
    } else{
        (*tabla_paginas)[index] = pVirtual;
    }
}
PVirtual* TablaPagina::eliminarPagina(int idPagina){
    if (tamano == 0){
        return nullptr;
    }

    int index = funcion_hash(idPagina);
    PVirtual* aux = (*tabla_paginas)[index];
    while (aux != nullptr){
        if (aux->obtenerPageNumber() == idPagina){
            if(aux->prev() != nullptr){
                aux->prev()->setNext(aux->next());
            }else{
                (*tabla_paginas)[index] = nullptr;
            }
            return aux;
        }
        aux = aux->next();
    }
    return nullptr;
}
PVirtual* TablaPagina::obtenerPagina(int idPagina){
    if (tamano == 0){
        return nullptr;
    }

    int index = funcion_hash(idPagina);
    PVirtual* aux = (*tabla_paginas)[index];
    while (aux != nullptr){
        if (aux->obtenerPageNumber() == idPagina){
            return aux;
        }
        aux = aux->next();
    }
    return nullptr;
}
PVirtual* TablaPagina::reemplazarPagina(PVirtual* pVirtual){
    if (tamano == 0){
        return nullptr;
    }

    // Obtiene pagina virtual a reemplazar
    PVirtual* pagina;
    if (algReemplazo == "optimo"){
        pagina = optimo();
    } else if (algReemplazo == "fifo"){
        pagina = fifo();
    } else if (algReemplazo == "lru"){
        pagina = lru();
    } else {
        pagina = lruReloj();
    }
    
    // Reemplaza la pagina del parametro por la obtenida con el algoritmo de reemplazo.
    if (pagina == nullptr){
        return nullptr;
    }
    if (pagina->prev() != nullptr){
        pagina->prev()->setNext(pVirtual);
    }else{
        (*tabla_paginas)[funcion_hash(pVirtual->obtenerPageNumber())] = pVirtual;
    }
    pVirtual->setNext(pagina->next());

    // Retorna la pagina reemplazada
    return pagina;
}
int TablaPagina::funcion_hash(int id){
    int nPrimo = 13;
    int resultado = (id * nPrimo) % capacidad;
    return resultado;
}

PVirtual* TablaPagina::optimo(){

}

PVirtual* TablaPagina::fifo(){

}

PVirtual* TablaPagina::lru(){

}

PVirtual* TablaPagina::lruReloj(){

}