#ifndef WORKER_H
#define WORKER_H

#include "Tool.h"
#include <string>
using namespace std;

class Worker{
   
    public:
    Worker(int _sellPrice); // constructor, sets sell price of worker;
    int miningRate; // gold mining rate per tick
    bool isUpgraded;
    int sellPrice; // sellPrice of the worker
    Tool* equippedTool;
    bool upgrade(); // upgrades worker 
    int mine(); // returns gold mined in one tick
    // void sell(); // sells worker for 'sellPrice' gold

};

#endif WORKER_H