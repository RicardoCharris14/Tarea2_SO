#include "../include/queue.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
circular_queue::circular_queue(int size):
    datas(size), 
    indexFront(0), 
    indexRear(0), 
    size_queue(size), 
    size_items(0) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << "logs/log_" << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S") << ".txt";
        logFile.open(ss.str(), std::ios::out | std::ios::app);
        if(!logFile.is_open()){
            throw std:: runtime_error("No se abrio el archivo log.");
        }
        logFile << BOLDGREEN << "[LOG] cola iniciada con una capacidad de " << size_queue << std::endl;

    }
    circular_queue::~circular_queue() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
void circular_queue::resize_queue(int new_size){
    std::vector<int> new_data(new_size);
    for(int i = 0; i < size_items; i++){
        new_data[i] = datas[(indexFront + i) % size_queue];
    }
    datas = new_data;
    indexFront = 0;
    indexRear = size_items;
    logFile << BOLDRED << "[LOG] La cola se redimensionó con nuevo tamaño de: " << new_size << RESET << std::endl;
    logFile.flush();
    size_queue = new_size;
}
void circular_queue::enqueue(int item){
    std::lock_guard<std::mutex> lock(mtx);
    if(isFull()){
        resize_queue(size_queue * 2);
        // duplicamos el tamaño de la cola si esta ya está llena
    }
    datas[indexRear] = item;
    indexRear = (indexRear + 1) % size_queue;
    // reindexamos el indice del final, de tal forma
    // que solo puede tomar valores en [0. size_queue - 1]
    size_items++;
    logFile << "[LOG] Enqueue: Elemento añadido = " << item << ", tamaño actual = " << size_items << "\n";
    logFile.flush();
}
 int circular_queue::dequeue(){
    std::lock_guard<std::mutex> lock(mtx);
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
    logFile << "[LOG] Dequeue: Elemento eliminado = " << item << ", tamaño actual = " << size_items << "\n";
    logFile.flush();
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

