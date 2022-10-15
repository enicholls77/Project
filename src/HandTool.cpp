
#include "HandTool.h"
#include <string>
using namespace std;

//Returns only the base multiplier as there is no powered element
double HandTool::getMiningMultiplier() {
    return (getBaseRate());
}

// to be implemented
void HandTool::upgrade(){
}

HandTool::HandTool(double baseRate_, string toolName_){
    baseRate = baseRate_;
    toolName = toolName_;
    upgraded = 0;
}