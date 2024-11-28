#include <"memoria_fisica.h">

MemFisica::MemFisica(int size) {
	this->size = size;
}

void MemFisica::getSize() {
	return this->size;
}

Marco MemFisica::obtenerMarcoDisp() {
	if(this->marcosPagina.empty()) {
		return nullptr;
	}
	else {
		Marco marcoDisponible = this->marcosPagina.back(); // ultimo elemento del vector
		this->marcosPagina.pop_back(); // quitamos el ultimo marco
		return marcoDisponible;
	}
}

bool MemFisica::agregarMarco(Marco* m) {
	if(this->marcosPagina.size() == this->size) {
		return false; // no se puede agregar marco
	}
	else if(this->marcosPagina.size() < this->size) {
		this->marcosPagina.push_back(m);
		return true;
	}
}