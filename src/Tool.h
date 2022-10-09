#ifndef TOOL_H
#define TOOL_H

class Tool {

    protected:
    //value of mining multiplier
    double baseRate;

    public:
    //returns mining multiplier
    double getBaseRate(){
        return baseRate;
    }
    virtual double getMiningMultiplier() = 0;

};

#endif //TOOL_H