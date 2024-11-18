#include "../include/consumer_producter.h"
#include <iostream>

void producer(monitor &monitor, int ID){
    for(int i = 0;i < 5; i++){
        monitor.produce(i + ID *100);
        std::cout << "Productor " << ID << " produjo: " << (i + ID * 100) << "\n";
    }
}
void comsumer(monitor &monitor, int ID){
    for (int i = 0; i < 5; i++){
        int item = monitor.consume();
        std::cout << "Consumidor " << ID << " consumió: " << item << "\n";
    }
    
}