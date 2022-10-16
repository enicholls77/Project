#ifndef TOOL_H
#define TOOL_H

#include <string>
using namespace std;

class Tool {

    protected:
    //value of mining multiplier
    double baseRate;
    //name of each tool, for shop displayer purposes
    string toolName;
    //will only have an impact on PowerTool and MegaDrill classes
    bool powered;
    

    public:
    //returns mining multiplier
    double getBaseRate();
    //getMiningMultipler will give miing multiplier of the tool, will be different for hand and power tools
    virtual double getMiningMultiplier() = 0;
    //retrieves tool name for display purposes
    string returnToolName();
    //upgrades the tool, will be different for PowerTools
    virtual void upgrade() = 0;
    //virtual powering for power tools once powered
    void setPowered();
    // price of tool
    double price;
    //shows if tool is upgraded or not
    bool upgraded;
    

};

#endif
