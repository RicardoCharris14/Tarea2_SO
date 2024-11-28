#include "memoria_fisica.h"

MemFisica::MemFisica(int capacity) {
	for (int i=1 ; i<=capacity ; i++){
		Marco* marco = new Marco(capacity-i);
		marcosPagina[i] = marco;
	}
	this->capacity = capacity;
}

Marco* MemFisica::obtenerMarcoDisp() {
	if(this->marcosPagina.empty()) {
		return nullptr;
	}
	else {
		Marco* marcoDisponible = this->marcosPagina.back(); // ultimo elemento del vector
		this->marcosPagina.pop_back(); // quitamos el ultimo marco
		return marcoDisponible;
	}
}

bool MemFisica::agregarMarco(Marco* m) {
	if(this->marcosPagina.size() == this->capacity) {
		return false; // no se puede agregar marco
	}
	else {
		this->marcosPagina.push_back(m);
		return true;
	}
}