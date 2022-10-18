#ifndef MOCKHANDTOOL_H
#define MOCKHANDTOOL_H

#include <gmock/gmock.h>

#include "../HandTool.h"

#include <string>
using namespace std;

class MockHandTool: public HandTool{
    
    public:
    //returns multiplier for tool, which is base rate of the tool
    MOCK_METHOD(double, getMiningMultiplier, ());
    MOCK_METHOD(void, upgrade, ());

    //initialiser with all required variables for the class
    MockHandTool(double baseRate_, string toolName_, double _price) : 
    HandTool(baseRate_, toolName_, _price){
        // baseRate = baseRate_;
        // toolName = toolName_;
        // upgraded = 0;
        // powerTool = 0;
        // price = _price;
    }
    // virtual HandTool* clone() const;

};
#endif