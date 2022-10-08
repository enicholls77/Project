#ifndef POWERTOOL_H
#define POWERTOOL_H

#include "Tool.h"
#include <string.h>
using namespace std;

class PowerTool: public Tool{
    protected:
    //power needed to run tool
    int powerNeeded;
    //bonus multiplier if powered
    double poweredMultiplier;
    

    public:
    //determines if tool is powered
    bool powered;

    //returns multiplier for tool, which is base rate + bonus rate from if tool is powered
    double getMiningMultiplier() {
        return (getBaseRate() + powered*poweredMultiplier);
    }

};

#endif POWERTOOL_H