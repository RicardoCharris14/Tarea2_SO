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