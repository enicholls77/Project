#ifndef HANDTOOL_H
#define HANDTOOL_H

#include "Tool.h"
#include <string>
using namespace std;

class HandTool: public Tool{
    
    public:
    //returns multiplier for tool, which is base rate of the tool
    double getMiningMultiplier();
    void upgrade();

    //initialiser with all required variables for the class
    HandTool(double baseRate_, string toolName_, double _price);
    virtual HandTool* clone() const;

};
#endif