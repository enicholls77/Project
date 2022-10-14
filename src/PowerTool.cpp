#include "Tool.h"
#include "PowerTool.h"
#include <string>
using namespace std;

//returns multiplier for tool, which is base rate + bonus rate from if tool is powered
double PowerTool::getMiningMultiplier() {
    return (getBaseRate() + powered * poweredMultiplier);
}
//returns power needed per tick
int PowerTool::getPowerNeeded() {
    return powerNeeded;
}
//changes status of powered based upon if the tool will be able to be powered or not
//to be used by TheGame class
void PowerTool::setpowered(bool ifPowered) {
    powered = ifPowered;
}

PowerTool::PowerTool(double baseRate_, string toolName_, int powerNeeded_, double poweredMultiplier_){
    baseRate = baseRate_;
    toolName = toolName_;
    powerNeeded = powerNeeded_;
    poweredMultiplier = poweredMultiplier_;
}