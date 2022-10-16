#include "Tool.h"
#include "Worker.h"
#include <string.h>
using namespace std;

Worker::Worker(int _price){// constructor, sets sell price of worker;
    price = _price;
    miningRate = 1;
}

double Worker::mine(){  // returns gold mined in one tick, if no tool, just mining rate of miner is returned, otherwise the 
                        // mining rate is multiplied by the multiplier of the tool
    if (isToolEquipped == 1){
        return (miningRate * equippedTool->getMiningMultiplier());
    }
    else {
        return miningRate;
    }
}

// Worker::~Worker(){
//     delete this; // TODO: is this dangerous ?
// }