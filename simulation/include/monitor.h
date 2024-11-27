#ifndef MONITOR_H
#define MONITOR_H

#include "../include/queue.h"
#include <condition_variable>
#include <mutex>

class monitor{
    private:
        circular_queue queue;
        std::mutex mtx;
        std::condition_variable notEmpty;
        std::condition_variable notFull;
    public:
        monitor(int size); // mismo size que el constructor de circular_queue

        void produce(int item);
        int consume();

};



#endif