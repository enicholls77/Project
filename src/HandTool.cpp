
#include "HandTool.h"
#include <string>
using namespace std;

//Returns only the base multiplier as there is no powered element
double HandTool::getMiningMultiplier() {
    return (getBaseRate());
}

// to be implemented
void HandTool::upgrade(){
    if (upgraded == 0) {
        upgraded = 1;
        baseRate = baseRate * 1.5;
    }
}

HandTool::HandTool(double baseRate_, string toolName_, double _price){
    baseRate = baseRate_;
    toolName = toolName_;
    upgraded = 0;
    powerTool = 0;
    price = _price;
}

HandTool* HandTool::clone() const  {
    return new HandTool (*this);
}