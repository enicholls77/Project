#include "Tool.h"
#include "PowerTool.h"
#include "MegaDrill.h"
#include <string>
using namespace std;

//Same constructor as PowerTool, however 
MegaDrill::MegaDrill(double baseRate_, string toolName_, double poweredMultiplier_, double _price){
    baseRate = baseRate_;
    toolName = toolName_;
    poweredMultiplier = poweredMultiplier_;
    price = _price;
    powerTool = 1;
    powered = 0;
    upgraded = 0;
}

void MegaDrill::upgrade(){
    if (upgraded == 0) {
        upgraded = 1;
        baseRate = baseRate * 5;
        poweredMultiplier = poweredMultiplier * 5;
    }
}

MegaDrill* MegaDrill::clone() const  {
    return new MegaDrill (*this);
}