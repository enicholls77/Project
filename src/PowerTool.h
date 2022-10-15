#ifndef POWERTOOL_H
#define POWERTOOL_H

#include "Tool.h"
#include <string>
using namespace std;

class PowerTool: public Tool{
    protected:
    //bonus multiplier if powered
    double poweredMultiplier;
    
    public:
    //returns multiplier for tool, which is base rate + bonus rate from if tool is powered
    double getMiningMultiplier() {
        return (getBaseRate() + powered * poweredMultiplier);
    }
    //basic constructor
    PowerTool();

    //constructor with all variables
    PowerTool(double baseRate_, string toolName_, double poweredMultiplier_);

    //uses ability, which will be seperate from MegaDrill's upgrade
    virtual void upgrade();
};
#endif //POWERTOOL_H