#ifndef MEGADRILL_H
#define MEGADRILL_H

#include "Tool.h"
#include "PowerTool.h"
#include <string>
using namespace std;

class MegaDrill: public PowerTool{

public:

    //constructor for a steel drill
    MegaDrill() {
       baseRate = 1;
       toolName = "Mega Drill";
       //when powered will have mining rate of 5 per tick, otherwise same as stone pickaxe
       poweredMultiplier = 4;
       //not powered by default
       powered = 0;
       //requires 3 power per tick
       powerNeeded = 3;
    }
};
#endif