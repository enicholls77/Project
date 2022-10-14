#include <string>
#include "Tool.h"
using namespace std;


//returns mining multiplier
double Tool::getBaseRate(){
    return baseRate;
}
//retrieves tool name for display purposes
string Tool::returnToolName(){
    return toolName;
}