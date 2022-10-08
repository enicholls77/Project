

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