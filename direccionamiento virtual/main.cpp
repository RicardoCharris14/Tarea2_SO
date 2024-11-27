#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "tabla_pagina.h"
#include "marco_pagina.h"
#include "pagina_virtual.h"
// compilar usando g++ main.cpp tabla_pagina.cpp marco_pagina.cpp pagina_virtual.cpp -o main (Linux)
// ejecutar usando ./main -m <n_marcos> -a <algoritmo> -f <file>
// ejemplo que funciona: ./main -m 3 -a fifo -f ref.txt


std::vector<int> leerReferenciasDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + nombreArchivo);
    }

    std::vector<int> referencias;
    std::string linea;
    std::getline(archivo, linea);
    std::stringstream ss(linea);

    int referencia;
    while (ss >> referencia) {
        referencias.push_back(referencia);
    }

    archivo.close();
    return referencias;
}

int main(int argc, char const *argv[]){
    if (argc != 7) {
        std::cerr << "Uso: ./mvirtual -m <num_marcos> -a <algoritmo> -f <archivo_referencias>" << std::endl;
        return 1;
    }

    int marcos = 0;
    std::string algoritmo;
    std::string archivoReferencias;

    // Procesar argumentos de línea de comandos
    for (int i = 1; i < argc; i += 2) {
        std::string argumento = argv[i];
        if (argumento == "-m") {
            marcos = std::stoi(argv[i + 1]);
        } else if (argumento == "-a") {
            algoritmo = argv[i + 1];
        } else if (argumento == "-f") {
            archivoReferencias = argv[i + 1];
        } else {
            std::cerr << "Argumento desconocido: " << argumento << std::endl;
            return 1;
        }
    }

    if (marcos <= 0) {
        std::cerr << "El número de marcos debe ser mayor a 0." << std::endl;
        return 1;
    }

    try {
        // Leer las referencias desde el archivo
        std::vector<int> referencias = leerReferenciasDesdeArchivo(archivoReferencias);

        // Crear la tabla de páginas con el algoritmo especificado
        TablaPagina tabla(algoritmo, marcos);

        int fallosDePagina = 0;

        // Procesar las referencias
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
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
