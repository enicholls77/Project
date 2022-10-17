#include "Tool.h"
#include "PowerTool.h"
#include <string>
using namespace std;

//returns multiplier for tool, which is base rate + bonus rate from if tool is powered
double PowerTool::getMiningMultiplier() {
    return (getBaseRate() + powered * poweredMultiplier);
}
//changes status of powered based upon if the tool will be able to be powered or not
//to be used by The Game class

PowerTool::PowerTool(double baseRate_, string toolName_, double poweredMultiplier_, double _price){
    baseRate = baseRate_;
    toolName = toolName_;
    poweredMultiplier = poweredMultiplier_;
    price = _price;
    powerTool = 1;
    powered = 0;
    upgraded = 0;
}
PowerTool::PowerTool(){
    baseRate = 0;
    toolName = "Error: Not real Tool";
    poweredMultiplier = 0;
    powerTool = 1;
    powered = 0;
}
//if not already upgraded, base rate and power multiplier are doubled
void PowerTool::upgrade(){
    if (upgraded == 0) {
        upgraded = 1;
        baseRate = baseRate * 3;
        poweredMultiplier = poweredMultiplier * 3;
    }

}

PowerTool* PowerTool::clone() const  {
    return new PowerTool (*this);
}