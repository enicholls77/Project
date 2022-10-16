#ifndef WORKER_H
#define WORKER_H

#include "Tool.h"
#include <string>
using namespace std;

class Worker{
   
    public:
    Worker(int _price); // constructor, sets sell price of worker;
    int miningRate; // gold mining rate per tick
    int price; // sellPrice of the worker
    bool isToolEquipped; //tells if a tool is equipped
    Tool* equippedTool;
    void upgrade(); // upgrades worker 
    double getMiningRate();
    double mine(); // returns gold mined in one tick

};

#endif //WORKER_H