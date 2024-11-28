#ifndef MEM_FISICA_H
#define MEM_FISICA_H
#include "marco_pagina.h"
#include <vector>

class MemFisica {
private:
	int size;
	std::vector<Marco*> marcosPagina;
public:
	MemFisica(int);
	int getSize();
	void setSize(int);
	Marco obtenerMarcoDisp(); // idea: retornar marco disponible o null en caso contrario
	bool agregarMarco(Marco*); // idea: ver cuantas entradas tiene el vector. Si es menor que size pushear.
};

#endif