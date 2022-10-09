#include "Tool.h"
#include "Worker.h"
#include <string.h>
using namespace std;

Worker::Worker(int _sellPrice){// constructor, sets sell price of worker;
    sellPrice = _sellPrice;
}

void Worker::upgrade(){ // upgrades worker 
    isUpgraded = true;
}

// TODO: is this needed?
// int Worker::activateAbility(){}

int Worker::mine(){ // returns gold mined in one tick
    return miningRate;
}

// TODO: sell function ???
// int Worker::sell(){ // returns gold mined in one tick
//     return miningRate;
// }

// Worker::~Worker(){
//     delete this; // TODO: is this dangerous ?
// }