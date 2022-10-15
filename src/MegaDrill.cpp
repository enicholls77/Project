#include "Tool.h"
#include "PowerTool.h"
#include "MegaDrill.h"
#include <string>
using namespace std;

//Same constructor as PowerTool, however 
MegaDrill::MegaDrill(double baseRate_, string toolName_, double poweredMultiplier_){
    baseRate = baseRate_;
    toolName = toolName_;
    poweredMultiplier = poweredMultiplier_;
}

void MegaDrill::upgrade(){
    if (upgraded == 0) {
        upgraded = 1;
        baseRate = baseRate * 3;
        poweredMultiplier = poweredMultiplier * 3;
    }
}