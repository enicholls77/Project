#ifndef STEELPICKAXE_H
#define STEELPICKAXE_H

#include "Tool.h"
#include "HandTool.h"
#include <string>
using namespace std;

class SteelPickaxe: public HandTool{

public:

    //constructor for a steel pickaxe
    SteelPickaxe() {
       baseRate = 1.5;
       toolName = "Steel Pickaxe";

    }


};




#endif