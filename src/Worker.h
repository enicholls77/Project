#ifndef WORKER_H
#define WORKER_H

#include "Tool.h"
#include <string>
using namespace std;

class Worker{
   
    public:
    Worker(int _price, int _id); // constructor, sets sell price of worker;
    int miningRate; // gold mining rate per tick
    int price; // sellPrice of the worker
    int id; // id of worker
    bool isToolEquipped; //tells if a tool is equipped
    Tool* equippedTool; //equipped tool
    double mine(); // returns gold mined in one tick

};

#endif //WORKER_H