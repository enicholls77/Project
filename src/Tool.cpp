#include <string>
#include "Tool.h"
using namespace std;


//returns mining multiplier
double Tool::getBaseRate(){
    return baseRate;
}

// //retrieves tool name for display purposes
// string Tool::returnToolName(){
//     return toolName;
// }

//if not already upgraded, doubles base rate of tool
void Tool::upgrade(){
    if (upgraded == 0){
        upgraded = 1;
        baseRate = baseRate * 2;
    }
}
void Tool::setPowered(){
    powered = 1;
}

void Tool::setUnPowered(){
    powered = 0;
}