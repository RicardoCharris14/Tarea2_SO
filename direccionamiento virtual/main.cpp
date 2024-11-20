#include <iostream>
#include <vector>
#include "tabla_pagina.h"
#include "marco_pagina.h"
#include "pagina_virtual.h"
// compilar usando g++ main.cpp tabla_pagina.cpp marco_pagina.cpp pagina_virtual.cpp -o main (Linux)
int main() {
    int marcos = 3; 
    std::string algoritmo = "lrureloj"; 
    std::vector<int> referencias = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}; 

    TablaPagina tabla(algoritmo, marcos);

    int fallosDePagina = 0;

    for (int i = 0; i < referencias.size(); ++i) {
        PVirtual* pagina = new PVirtual(referencias[i], nullptr, nullptr, nullptr);

        PVirtual* paginaReemplazada = tabla.insertarPagina(pagina, referencias, i);
        if (paginaReemplazada != nullptr) {
            ++fallosDePagina; 
            delete paginaReemplazada;
        }

        std::cout << "Procesada referencia: " << referencias[i] << std::endl;
    }

    std::cout << "\nNúmero total de fallos de página: " << fallosDePagina << std::endl;

    return 0;
}
