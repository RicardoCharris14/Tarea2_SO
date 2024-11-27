#ifndef MONITOR_H
#define MONITOR_H

#include "../include/queue.h"
#include <condition_variable>
#include <mutex>
#include <chrono>

class monitor{
    private:
        circular_queue queue;
        std::mutex mtx;
        bool tiempo_iniciado;
        std::chrono::time_point<std::chrono::high_resolution_clock> tInicial;
        int tObjetivo;
    public:
        monitor(int size); // mismo size que el constructor de circular_queue

        void produce(int item, int id);
        int consume(int id);
        void startTime(int time);

};



#endif