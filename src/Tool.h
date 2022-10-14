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

    public:
    //returns mining multiplier
    double getBaseRate();
    //getMiningMultipler will give miing multiplier of the tool, will be different for hand and power tools
    virtual double getMiningMultiplier() = 0;
    //retrieves tool name for display purposes
    string returnToolName();

};

#endif
