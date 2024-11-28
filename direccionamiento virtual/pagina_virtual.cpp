#include "pagina_virtual.h"
#include <iostream>

PVirtual::PVirtual(int pageNumber, Marco* marco = nullptr , PVirtual* prev = nullptr, PVirtual* next = nullptr){
    this->pageNumber = pageNumber;
    this->marcoAsociado = marco;
    this->nextP = next;
    this->prevP = prev;
}

PVirtual* PVirtual::next(){
    return this->nextP;
}
    
PVirtual* PVirtual::prev(){
    return this->prevP;
}

void PVirtual::setNext(PVirtual* pagina){
    PVirtual* aux = nextP;
    nextP = pagina;
    delete(aux);
}

void PVirtual::setPrev(PVirtual* pagina){
    PVirtual* aux = prevP;
    prevP = pagina;
    delete(aux);
}

void PVirtual::asignarMarco(Marco* marco){
    this->marcoAsociado = marco;
}

Marco* PVirtual::obtenerMarco(){
    return this->marcoAsociado;
}

int PVirtual::obtenerPageNumber(){
    return pageNumber;
}

bool PVirtual::getRefBit(){
    return this->bitReferencia;
}

void PVirtual::setRefBit(bool bit_referencia){
    this->bitReferencia = bit_referencia;
}