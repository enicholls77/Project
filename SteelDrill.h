#ifndef STEELDRILL_H
#define STEELDRILL_H

#include "Tool.h"
#include "PowerTool.h"
#include <string>
using namespace std;

class SteelDrill: public PowerTool{

public:
    //constructor for a steel drill
    SteelDrill() {
       baseRate = 1;
       toolName = "Steel Drill";
       //when powered will have mining rate of 3 per tick, otherwise same as stone pickaxe
       poweredMultiplier = 2;
       //not powered by default
       powered = 0;
       //requires 1 power per tick
       powerNeeded = 1;
    }
};
#endif