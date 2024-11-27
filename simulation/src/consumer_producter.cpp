#include "../include/consumer_producter.h"
#include <iostream>
#include <chrono>

void producter(monitor &monitor, int ID){
    
    monitor.produce(ID *100, ID);
    
}
void consumer(monitor &monitor, int ID){
    
    int item;
    item = monitor.consume(ID);
    
}