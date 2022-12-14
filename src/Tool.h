#ifndef TOOL_H
#define TOOL_H

#include <string>
using namespace std;

class Tool {

    protected:
    //value of mining multiplier
    double baseRate;
    //will only have an impact on PowerTool and MegaDrill classes
    bool powered;
    

    public:
    //name of each tool, for shop displayer purposes
    string toolName;
    //returns mining multiplier
    double getBaseRate();
    //getMiningMultipler will give miing multiplier of the tool, will be different for hand and power tools
    virtual double getMiningMultiplier() = 0;
    //retrieves tool name for display purposes
    // string returnToolName();
    // //upgrades the tool, will be different for PowerTools
    virtual void upgrade() = 0;
    //virtual powering for power tools once powered
    void setPowered();
    // price of tool
    void setUnPowered();
    double price;
    //shows if tool is upgraded or not
    bool upgraded;
    //tells if the tools is a PowerTool or not
    bool powerTool;
    virtual Tool * clone () const = 0;  // Virtual constructor (copying) 

};

#endif
