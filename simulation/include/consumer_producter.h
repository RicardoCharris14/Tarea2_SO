#ifndef CONSUMER_PRODUCTER_H
#define CONSUMER_PRODUCTER_H

#include "monitor.h"
#include <thread>


void consumer(monitor &monitor, int ID, int time);
void producter(monitor &monitor, int ID);



#endif