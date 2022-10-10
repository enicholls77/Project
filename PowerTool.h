#ifndef POWERTOOL_H
#define POWERTOOL_H

#include "Tool.h"
#include <string>
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
        return (getBaseRate() + powered * poweredMultiplier);
    }
    //returns power needed per tick
    int getPowerNeeded() {
        return powerNeeded;
    }
    //changes status of powered based upon if the tool will be able to be powered or not
    //to be used by TheGame class
    void setpowered(bool ifPowered) {
        powered = ifPowered;
    }

};

#endif POWERTOOL_H