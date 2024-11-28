#include "tabla_pagina.h"
#include <iostream>


TablaPagina::TablaPagina(MemFisica memoria, std::string algReemplazo, int capacidad) : memoria(memoria){
    if (algReemplazo != "fifo" && algReemplazo != "lru" && 
        algReemplazo != "lrureloj" && algReemplazo != "optimo") {
        throw std::invalid_argument("Algoritmo no válido. Use 'fifo', 'lru', 'lrureloj' o 'optimo'.");
    }
    this->algReemplazo = algReemplazo;
    this->capacidad = capacidad;
    this->keys = new int(capacidad);
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
PVirtual* TablaPagina::insertarPagina(PVirtual* pVirtual, const std::vector<int>& referencias = std::vector<int>(), int posicionActual = -1) {
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

    //Se asigna un marco fisico a la pagina virtual
    Marco* marco = memoria.obtenerMarcoDisp();
    pVirtual->asignarMarco(marco);

    //Revisa si hay un elemento en la posicion obtenida por el hash, si lo hay busca un espacio en la lista enlazada, si no,
    //inserta el nuevo.
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

    //se añade a la cola fifo
    fifoQueue.push(pVirtual);

    //se añade a estructuras lru
    lruList.push_front(pVirtual);
    lruMap.emplace(pVirtual->obtenerPageNumber(), lruList.begin());

    keys[tamano] = pVirtual->obtenerPageNumber();
    tamano++;
    std::cout << "Entra pagina: " << pVirtual->obtenerPageNumber() << " | marco obtenido: " << pVirtual->obtenerMarco()->getId() << std::endl;
    return nullptr;
}

PVirtual* TablaPagina::eliminarPagina(int idPagina){
    if (tamano == 0){
        return nullptr;
    }

    // busca la pagina en la posicion obtenida por la funcion hash y en la lista enlazada, si la encuentra la retira y la retorna.
    int index = funcion_hash(idPagina);
    PVirtual* aux = (*tabla_paginas)[index];
    while (aux != nullptr){
        if (aux->obtenerPageNumber() == idPagina){
            if(aux->prev() != nullptr){
                aux->prev()->setNext(aux->next());
            }else{
                (*tabla_paginas)[index] = nullptr;
            }
            //Elimina la key de la pagina retirada de keys
            for (int i=0 ; i<tamano ; i++){
                if (keys[i] == idPagina){
                    for (i ; i<tamano-1 ; i++){
                        keys[i] = keys[i+1];
                    }
                    break;
                }
            }
            //Se devuelve a memoria el marco de la pagina eliminada
            Marco* marco = aux->obtenerMarco();
            aux->asignarMarco(nullptr);
            memoria.agregarMarco(marco);
            
            tamano--;
            std::cout << "Sale pagina: " << idPagina << " | marco soltado: " << marco->getId() << std::endl;
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

    //busco en la posicion obtenida por el hash
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


    // Eliminar la pagina anterior
    eliminarPagina(pagina->obtenerPageNumber());
    //insertar la nueva pagina
    insertarPagina(pVirtual);

    return pagina;
}

int TablaPagina::funcion_hash(int id){
    int nPrimo = 13;
    int resultado = (id * nPrimo) % capacidad;
    return resultado;
}

PVirtual* TablaPagina::optimo(const std::vector<int>& referencias, int posicionActual) {

    if (referencias.empty() || posicionActual >= referencias.size()) {
    throw std::invalid_argument("Referencias inválidas o posición fuera de rango.");
    }


    PVirtual* paginaReemplazada = nullptr;
    int indiceMasTardio = -1;

    // Buscar la página menos usada en el futuro
    for (int i = 0; i < tamano; ++i) {
        PVirtual* pagina = obtenerPagina(keys[i]);
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

    PVirtual* paginaReemplazada = fifoQueue.front(); // la mas reciente
    fifoQueue.pop();

    return paginaReemplazada;
}


PVirtual* TablaPagina::lru() {

    // Página menos recientemente usada (final de la lista)
    PVirtual* paginaReemplazada = lruList.back();
    lruList.pop_back();
    lruMap.erase(paginaReemplazada->obtenerPageNumber());

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
            if (pagina->getRefBit()) { // Si el bit de referencia es 0
                PVirtual* paginaReemplazada = pagina;
                (*tabla_paginas)[indice_reloj] = nullptr; // Liberar la página
                indice_reloj = (indice_reloj + 1) % capacidad; // Avanzar el puntero
                return paginaReemplazada;
            } else {
                // Si el bit es 1, lo reseteamos a 0
                pagina->setRefBit(false);
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

