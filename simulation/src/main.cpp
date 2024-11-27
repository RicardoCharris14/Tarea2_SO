#include "../include/consumer_producter.h"
#include "../include/queue.h"
#include "../include/monitor.h"
// colores para la salida del programa
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <vector>
void StartSimulator(int productores, int consumidores, int sizeQueue, int time, int numElemets){
    monitor shared_monitor(sizeQueue); // instanciamos la clase monitor
    std::vector<std::thread> producter_thread; // creamos un arreglo de hebras para cada productor
    for(int i = 0; i < productores; i++){
        //creamos un hebra para cada productor
        producter_thread.emplace_back(producter, std::ref(shared_monitor),i);
        // agregamos la nueva hebra en el vector producter_thread, esta hebra
        // ejecutara la funcion 'producter', esto lo hace atravez de una referencia a la instancia
        // shared_monitor y por ultimo el indice 'i' es el ID del productor
    }

    std::vector<std::thread> consumer_thread; // creamos un arreglo de hebras para cada consumidor
    for (int i = 0; i < consumidores; i++){
        consumer_thread.emplace_back(consumer, std::ref(shared_monitor), i, time);
    }
    for(auto &p: producter_thread){
        p.join();
    }
    for(auto &c: consumer_thread){
        c.join();
    }


}

int main(int argc, char *argv[]){
    int opt;
    int productores;
    int consumidores;
    int sizeQueue;
    int time;

    if(argc != 9){
        std::cout << "argumentos incorrectos, uso correcto:" << std::endl;
        std::cout << argv[0] << " -p <numero productores> -c <numero consumidores> -s <tamaño cola> -t <tiempo espera consumidores>" << std::endl;
        exit(EXIT_FAILURE);
    }
    while ((opt = getopt(argc, argv, "p:c:s:t:")) != -1){
        switch(opt){
            case 'p':
                productores = atoi(optarg);
                // atoi captura el valor de aptarg, o sea lo que viene despues del -p
                break;
            case 'c':
                consumidores = atoi(optarg);
                break;
            case 's':
                sizeQueue = atoi(optarg);
                break;
            case 't':
                time = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Ejemplo de uso: %s -p <productores> -c <consumidores> -s <tamano_cola> -t <tiempo_espera>\n", argv[0]);
                exit(EXIT_FAILURE);

        }
    }
    int opcion = 0;
    int numberElemets = 10;
    while(opcion == 0){
        std::cout << BOLDGREEN << "Bienvenido \n Nuestro simulador ofrece dos opciones para el uso de los productores. Ingrese su opcion:  \n [1] Para que cada productor agregue el tamaño predeterminado de elementos que puede producir (10 elementos) \n [2] Para definir usted el numero de elementos \n Presione -1 si desea finalizar el programa \n" << std::endl;
        std::cin >> opcion;
        if(opcion == 1){
            // llamar a la funcion de la cola
            StartSimulator(productores, consumidores, sizeQueue, time, numberElemets);
        }else if (opcion == 2){
            std::cout << "\n Ingrese el numero de elementos para los productores \n" << std::endl;
            std::cin >> numberElemets;
            if(!(numberElemets > 0)){
                std::cout << "\n Porfavor ingrese un numero valido de elementos \n" << std::endl;
            }
            StartSimulator(productores, consumidores, sizeQueue, time, numberElemets);
        }else if(opcion == -1){
            std::cout << " \n Finalizando Programa ...\n" << std::endl;
            break;
        }else{
            std::cout<< BOLDRED << "\n ¡¡Ingrese Una opcion valida porfavor!! \n" << RESET << std::endl;
            opcion = 0;
        }
        
    }


    return 0;
}
