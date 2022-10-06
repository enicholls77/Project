#ifndef HANDTOOL_H
#define HANDTOOL_H

#include "Tool.h"
#include <string.h>
using namespace std;

class HandToolTool: public Tool{
   
    public:
    //returns multiplier for tool, which is base rate of the tool
    double getMiningMultiplier() {
        return (getBaseRate());
    }

};

#endif HANDTOOL_H