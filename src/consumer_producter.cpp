#include "../include/consumer_producter.h"
#include <iostream>

void producer(monitor &monitor, int ID){
    for(int i = 0;i < 5; i++){
        monitor.produce(i + ID *100);
        std::cout << "Productor " << ID << " produjo: " << (i + ID * 100) << "\n";
    }
}
void consumer(monitor &monitor, int ID, int time){
    for (int i = 0; i < 5; i++){
        int item;
        try{
           item = monitor.consume();
           std::cout << "Consumidor " << ID << " consumió: " << item << "\n";

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout << "Consumidor " << ID << " consumió: " << item << "\n";
    }
    
}