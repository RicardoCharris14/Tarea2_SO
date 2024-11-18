#include "../include/consumer_producter.h"
#include "../include/queue.h"
#include "../include/monitor.h"

#include <iostream>
#include <unistd.h>
#include <cstdlib>


int main(int argc, char *argv[]){
    int opt;
    int productores;
    int consumidores;
    int sizeQueue;
    int time;

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
    


    return 0;
}
