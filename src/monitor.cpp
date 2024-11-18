#include "../include/monitor.h"

monitor::monitor(int size) : queue(size) {}

void monitor::produce(int item){
    std::unique_lock <std::mutex> lock(mtx);
    // bloque y libera automaticamente la seccion critica
    // para esto usamos unique_lock
    queue.enqueue(item);
    notEmpty.notify_one();
    // .notify_one() notifica a una hebra/consumidor
    // que la cola ya no esta vacía
    


}