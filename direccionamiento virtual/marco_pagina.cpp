#include "marco_pagina.h"

Marco::Marco(int id_marco){
    this->id = id_marco;
}

int Marco::getId(){
    return this->id;
}

bool Marco::getRefBit(){
    return this->bit_referencia;
}

void Marco::setRefBit(bool bit_referencia){
    this->bit_referencia = bit_referencia;
}