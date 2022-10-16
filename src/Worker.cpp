#include "Tool.h"
#include "Worker.h"
#include <string.h>
using namespace std;

Worker::Worker(int _sellPrice){// constructor, sets sell price of worker;
    sellPrice = _sellPrice;
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

// TODO: sell function ???
// int Worker::sell(){ // returns gold mined in one tick
//     return miningRate;
// }

// Worker::~Worker(){
//     delete this; // TODO: is this dangerous ?
// }