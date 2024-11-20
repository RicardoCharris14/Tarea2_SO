#include "tabla_pagina.h"

TablaPagina::TablaPagina(std::string algReemplazo, int capacidad) {
    if (algReemplazo != "fifo" && algReemplazo != "lru" && 
        algReemplazo != "lrureloj" && algReemplazo != "optimo") {
        throw std::invalid_argument("Algoritmo no válido. Use 'fifo', 'lru', 'lrureloj' o 'optimo'.");
    }
    this->algReemplazo = algReemplazo;
    this->capacidad = capacidad;
    tamano = 0;
    tabla_paginas = new std::vector<PVirtual*>(capacidad, nullptr);
    indice_reloj = 0; // Solo usado por LRU-Reloj
}

/**
 * @brief La funcion inserta la pagina virtual entregada por parametro a la tabla de 
 * pagina, en caso de que la tabla este a su capacidad maxima, reemplaza una pagina
 * determinada por el algoritmo de reemplazo seleccionado.
 * @param referencias Vector que contiene las referencias futuras de páginas.
 * Se utiliza únicamente para el algoritmo Óptimo.
 * @param posicionActual Posición actual en el vector de referencias.
 * Se utiliza para calcular las referencias futuras en el algoritmo Óptimo.
 * @param pVirtual pagina virtual a insertar
 * @return PVirtual* pagina que fue reemplazada o nullptr si no reemplaza ninguna pagina.
 */
PVirtual* TablaPagina::insertarPagina(PVirtual* pVirtual, const std::vector<int>& referencias, int posicionActual) {
    int idPagina = pVirtual->obtenerPageNumber();
    PVirtual* paginaExistente = obtenerPagina(idPagina);

    if (paginaExistente != nullptr) {
        // Página ya está cargada; actualizar LRU
        actualizarLRU(paginaExistente);
        return nullptr; // No hay fallo de página
    }  

    if (tamano == capacidad) {
        // Pasar referencias y posición actual para el algoritmo Óptimo
        PVirtual* pagReemplazada = reemplazarPagina(pVirtual, referencias, posicionActual);
        return pagReemplazada;
    }

    int index = funcion_hash(pVirtual->obtenerPageNumber());
    if ((*tabla_paginas)[index] != nullptr) {
        PVirtual* aux = (*tabla_paginas)[index];
        while (aux->next() != nullptr) {
            aux = aux->next();
        }
        aux->setNext(pVirtual);
    } else {
        (*tabla_paginas)[index] = pVirtual;
    }

    fifoQueue.push(pVirtual);
    tamano++;
    return nullptr;
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
            tamano--;
            return aux;
        }
        aux = aux->next();
    }
    tamano--;
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
PVirtual* TablaPagina::reemplazarPagina(PVirtual* pVirtual, const std::vector<int>& referencias, int posicionActual) {
    if (tamano == 0) {
        return nullptr;
    }

    PVirtual* pagina = nullptr;

    // Determinar el algoritmo de reemplazo
    if (algReemplazo == "fifo") {
        pagina = fifo();
    } else if (algReemplazo == "lru") {
        pagina = lru();
    } else if (algReemplazo == "lrureloj") {
        pagina = lruReloj();
    } else if (algReemplazo == "optimo") {
        pagina = optimo(referencias, posicionActual);
    } else {
        throw std::runtime_error("Algoritmo no reconocido en reemplazarPagina.");
    }


    // Liberar el marco de la página reemplazada
    if (pagina != nullptr && pagina->obtenerMarco()) {
        pagina->obtenerMarco()->setRefBit(false);
    }

    // Reemplazar la página
    if (pagina != nullptr) {
        if (pagina->prev() != nullptr) {
            pagina->prev()->setNext(pVirtual);
        } else {
            (*tabla_paginas)[funcion_hash(pVirtual->obtenerPageNumber())] = pVirtual;
        }
        pVirtual->setNext(pagina->next());
    }

    return pagina;
}

int TablaPagina::funcion_hash(int id){
    int nPrimo = 13;
    int resultado = (id * nPrimo) % capacidad;
    return resultado;
}

PVirtual* TablaPagina::optimo(const std::vector<int>& referencias, int posicionActual) {

    if (tamano == 0) {
        return nullptr;
    }

    if (referencias.empty() || posicionActual >= referencias.size()) {
    throw std::invalid_argument("Referencias inválidas o posición fuera de rango.");
    }


    PVirtual* paginaReemplazada = nullptr;
    int indiceMasTardio = -1;

    // Buscar la página menos usada en el futuro
    for (int i = 0; i < capacidad; ++i) {
        PVirtual* pagina = (*tabla_paginas)[i];
        if (pagina == nullptr) continue;

        // Buscar próxima ocurrencia
        int proximaOcurrencia = -1;
        for (int j = posicionActual + 1; j < referencias.size(); ++j) {
            if (referencias[j] == pagina->obtenerPageNumber()) {
                proximaOcurrencia = j;
                break;
            }
        }

        if (proximaOcurrencia == -1) {  // si no se usará nunca más
            return pagina;
        }

        if (proximaOcurrencia > indiceMasTardio) {
            indiceMasTardio = proximaOcurrencia;
            paginaReemplazada = pagina;
        }
    }

    return paginaReemplazada;
}

PVirtual* TablaPagina::fifo() {
    if (fifoQueue.empty()) {
        return nullptr;
    }

    PVirtual* paginaReemplazada = fifoQueue.front(); // la mas reciente
    fifoQueue.pop();

    if (paginaReemplazada->obtenerMarco()) {
        paginaReemplazada->obtenerMarco()->setRefBit(false);
    }

    // Eliminar la página de la tabla hash
    int index = funcion_hash(paginaReemplazada->obtenerPageNumber());
    PVirtual* aux = (*tabla_paginas)[index];
    PVirtual* prev = nullptr;

    while (aux != nullptr) {
        if (aux->obtenerPageNumber() == paginaReemplazada->obtenerPageNumber()) {
            if (prev == nullptr) {
                (*tabla_paginas)[index] = aux->next();
            } else {
                prev->setNext(aux->next());
            }
            break;
        }
        prev = aux;
        aux = aux->next();
    }

    return paginaReemplazada;
}


PVirtual* TablaPagina::lru() {
    if (lruList.empty()) {
        return nullptr;
    }

    // Página menos recientemente usada (final de la lista)
    PVirtual* paginaReemplazada = lruList.back();
    lruList.pop_back();
    lruMap.erase(paginaReemplazada->obtenerPageNumber());

    // Liberar el marco de la página reemplazada
    if (paginaReemplazada->obtenerMarco()) {
        paginaReemplazada->obtenerMarco()->setRefBit(false);
    }

    // Eliminar la página de la tabla hash
    int index = funcion_hash(paginaReemplazada->obtenerPageNumber());
    PVirtual* aux = (*tabla_paginas)[index];
    PVirtual* prev = nullptr;

    while (aux != nullptr) {
        if (aux->obtenerPageNumber() == paginaReemplazada->obtenerPageNumber()) {
            if (prev == nullptr) {
                (*tabla_paginas)[index] = aux->next();
            } else {
                prev->setNext(aux->next());
            }
            break;
        }
        prev = aux;
        aux = aux->next();
    }

    return paginaReemplazada;
}

void TablaPagina::actualizarLRU(PVirtual* pVirtual) {
    // Mover la página al frente de la lista
    if (lruMap.find(pVirtual->obtenerPageNumber()) != lruMap.end()) {
        lruList.erase(lruMap[pVirtual->obtenerPageNumber()]);
    }
    lruList.push_front(pVirtual);
    lruMap[pVirtual->obtenerPageNumber()] = lruList.begin();
}


PVirtual* TablaPagina::lruReloj() {
    int vueltas = 0; // Contador de vueltas completas

    while (vueltas < 2) { // Limitar a dos vueltas completas
        PVirtual* pagina = (*tabla_paginas)[indice_reloj];

        if (pagina != nullptr) {
            Marco* marco = pagina->obtenerMarco();
            if (marco) {
                if (!marco->getRefBit()) { // Si el bit de referencia es 0
                    PVirtual* paginaReemplazada = pagina;
                    (*tabla_paginas)[indice_reloj] = nullptr; // Liberar la página
                    indice_reloj = (indice_reloj + 1) % capacidad; // Avanzar el puntero
                    return paginaReemplazada;
                } else {
                    // Si el bit es 1, lo reseteamos a 0
                    marco->setRefBit(false);
                }
            }
        }

        indice_reloj = (indice_reloj + 1) % capacidad; // Avanzar circularmente

        if (indice_reloj == 0) { // Si completa una vuelta
            vueltas++;
        }
    }

    // Si no se encuentra ninguna página reemplazable
    throw std::runtime_error("No se pudo encontrar una página reemplazable en LRU-Reloj.");
}

