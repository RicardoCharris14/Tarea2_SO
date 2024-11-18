#ifndef PAGINA_VIRTUAL_H
#define PAGINA_VIRTUAL_H

#include "marco_pagina.h"

class PVirtual{
private:
    int pageNumber;
    Marco* marcoAsociado;
    PVirtual* nextP;
    PVirtual* prevP;
public:
    PVirtual(int, Marco* ,PVirtual*, PVirtual*);
    void asignarMarco(Marco*);
    Marco* obtenerMarco();
    PVirtual* next();
    PVirtual* prev();
    void setNext(PVirtual*);
    void setPrev(PVirtual*);
    int obtenerPageNumber();
};

#endif