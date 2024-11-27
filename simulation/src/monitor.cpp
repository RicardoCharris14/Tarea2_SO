#include "../include/monitor.h"
#include <fstream>
#include <thread>

std::ofstream logFile;

monitor::monitor(int size) : queue(size) {
    tiempo_iniciado = false;
    logFile.open("simulation.log", std::ios::out | std::ios::app);
}

void monitor::produce(int item, int id){
    std::unique_lock <std::mutex> lock(mtx);
    // bloque y libera automaticamente la seccion critica
    // para esto usamos unique_lock
    queue.enqueue(item);
    logFile << "Producido: " << item << "\n";
    std::cout << "Productor " << id << " produjo: " << (id * 100) << "\n";
    // .notify_one() notifica a una hebra/consumidor
    // que la cola ya no esta vacía
}

int monitor::consume(int id){
    std::unique_lock <std::mutex> lock(mtx);
    if(tiempo_iniciado){
        auto tActual = std::chrono::high_resolution_clock::now();
        auto lapso = std::chrono::duration_cast<std::chrono::milliseconds>(tActual - tInicial).count();
        if(lapso >= tObjetivo){
            exit(0);
        }
    }
    while(queue.isEmpty()){
        if(tiempo_iniciado) exit(0);
        lock.unlock();
        std::this_thread::yield();
        lock.lock();

    }
    int item = queue.dequeue();
    logFile << "Consumido: " << item << "\n";
    std::cout << "Consumidor " << id << " consumió: " << item << "\n";

    return item;
}

void monitor::startTime(int time){
    tObjetivo = time * 1000;
    tiempo_iniciado = true;
    tInicial = std::chrono::high_resolution_clock::now();
}