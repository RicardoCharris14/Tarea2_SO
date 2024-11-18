#ifndef QUEUE_H
#define QUEUE_H

#include <vector>       // libreria para hacer vectores
#include <mutex>        // libreria para usar mutex

class circular_queue
{
private:
    std::vector<int> datas; // Guardar los datos
    int indexFront;         // indice para el inicio de la cola
    int indexRear;          // indice para el final de la cola
    int size_queue;        // tamaño total de la cola
    int size_items;        // cuantos elementos hay en la cola
    std::mutex mtx;         // semaforo mutex

    void resize_queue(int new_size); // funcion para modificar el tamaño de la cola
public:
    circular_queue(int size); // constructor de la cola
    void enqueue(int item); // añadir elementos
    int dequeue();          // quitar elemento
    bool isEmpty();         // verifica si esta vacia 
    bool isFull();          // verifica si esta llena
    int getSize_items();    // cuantos elementos hay en la cola
};


#endif 