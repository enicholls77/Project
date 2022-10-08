#ifndef WORKER_H
#define WORKER_H

#include "Tool.h"
#include <string.h>
using namespace std;

class Worker{
   
    public:
    Worker(int _sellPrice); // constructor, sets sell price of worker;
    int miningRate;
    bool isUpgraded;
    Tool* equippedTool;
    bool upgrade(); // upgrades worker 
    int mine(); // returns gold mined in one tick
    int sellPrice; // returns sellPrice;

};

#endif WORKER_H