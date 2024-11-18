#include "../include/queue.h"
#include <stdexcept>

circular_queue::circular_queue(int size):
    datas(size), 
    indexFront(0), 
    indexRear(0), 
    size_queue(size), 
    size_items(0) {}
void circular_queue::resize_queue(int new_size){
    std::vector<int> new_data(new_size);
    for(int i = 0; i < size_items; i++){
        new_data[i] = datas[(indexFront + i) % size_queue];
    }
    datas = new_data;
    indexFront = 0;
    indexRear = size_items;
    size_queue = new_size;
}
void circular_queue::enqueue(int item){
    if(isFull()){
        resize_queue(size_queue * 2);
        // duplicamos el tamaño de la cola si esta ya está llena
    }
    datas[indexRear] = item;
    indexRear = (indexRear + 1) % size_queue;
    // reindexamos el indice del final, de tal forma
    // que solo puede tomar valores en [0. size_queue - 1]
    size_items++;
}
 int circular_queue::dequeue(){
    if(isEmpty()){
        throw std::runtime_error("La cola esta vacía \n Ingresa elementos para realizar la operacion: ");
    }
    int item = datas[indexFront];
    indexFront = (indexFront + 1) % size_queue;
    // misma idea para reidexar y manatener el inidice dentro de los limites de la cola
    size_items--;
    if(size_items > 0 && size_items == int(size_queue/4)){
        resize_queue(size_queue / 2);
        // reducimos el tamaño de la cola para ahorrar espacio
        // agregamos dinamismo a la cola
    }
    return item;
 }

 bool circular_queue::isEmpty() const{
    return size_items == 0;
 }
 bool circular_queue ::isFull() const{
    return size_items == size_queue;
 }
int circular_queue ::getSize_items() const{
    return size_items;
}

