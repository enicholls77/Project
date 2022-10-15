#ifndef STONEPICKAXE_H
#define STONEPICKAXE_H

#include "Tool.h"
#include "HandTool.h"
#include <string>
using namespace std;

class StonePickaxe: public HandTool{

public:

    //constructor for a stone pickaxe
    StonePickaxe() {
       baseRate = 1;
       toolName = "Stone Pickaxe";

    }


};




#endif