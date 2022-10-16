#include "Tool.h"
#include "PowerTool.h"
#include <string>
using namespace std;

//returns multiplier for tool, which is base rate + bonus rate from if tool is powered
double PowerTool::getMiningMultiplier() {
    return (getBaseRate() + powered * poweredMultiplier);
}
//changes status of powered based upon if the tool will be able to be powered or not
//to be used by TheGame class

PowerTool::PowerTool(double baseRate_, string toolName_, double poweredMultiplier_){
    baseRate = baseRate_;
    toolName = toolName_;
    poweredMultiplier = poweredMultiplier_;
    price = 20;
}
PowerTool::PowerTool(){
    baseRate = 0;
    toolName = "Error: Not real Tool";
    poweredMultiplier = 0;
}
//if not already upgraded, base rate and power multiplier are doubled
void PowerTool::upgrade(){
    if (upgraded == 0) {
        upgraded = 1;
        baseRate = baseRate * 5;
        poweredMultiplier = poweredMultiplier * 5;
    }
}