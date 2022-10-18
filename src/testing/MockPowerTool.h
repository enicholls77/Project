#ifndef MOCKPOWERTOOL_H
#define MOCKPOWERTOOL_H

#include <gmock/gmock.h>

#include "../PowerTool.h"

#include <string>
using namespace std;

class MockPowerTool: public PowerTool{
    public:
    //returns multiplier for tool, which is base rate + bonus rate from if tool is powered
    //constructor with all variables
    // MOCK_METHOD(double, getMiningMultiplier, ());
    // MOCK_METHOD(void, upgrade,());

    MockPowerTool(double baseRate_, string toolName_, double poweredMultiplier_, double _price):
    PowerTool(baseRate_, toolName_, poweredMultiplier_, _price){
        powerTool = 1;
    }

    //uses ability, which will be seperate from MegaDrill's upgrade
};
#endif 