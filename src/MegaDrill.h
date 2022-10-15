#ifndef MEGADRILL_H
#define MEGADRILL_H

#include "Tool.h"
#include "PowerTool.h"
#include <string>
using namespace std;

class MegaDrill: public PowerTool{

public:

    //constructor for mega drill
    MegaDrill(double baseRate_, string toolName_, double poweredMultiplier_);
    //upgrading which will be better that PowerTool's upgrade
    void upgrade();

};
#endif