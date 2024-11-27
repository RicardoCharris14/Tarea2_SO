#include "../include/consumer_producter.h"
#include <iostream>
#include <chrono>

void producter(monitor &monitor, int ID){
    
    monitor.produce(ID *100);
    std::cout << "Productor " << ID << " produjo: " << (ID * 100) << "\n";
    
}
void consumer(monitor &monitor, int ID){
    
    int item;
    item = monitor.consume();
    std::cout << "Consumidor " << ID << " consumió: " << item << "\n";
    
}