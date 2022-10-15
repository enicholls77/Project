#include <cmath>

#include "HandTool.h"
#include "Worker.h"
#include "Game.h"

using namespace std;

// default constructor
Game::Game(){
    tick = 0;
    tickLimit = 2400;
    ticksPerSecond = 1; 

    Worker* worker;
    worker = new Worker(5);
    HandTool* pick = new HandTool(1, "Pickaxe");
    worker->equippedTool = pick;
    worker->isToolEquipped = true;
    workers.push_back(worker);
}

Game::Game(int _tickLimit, int _ticksPerSecond){ // constructor for setting custom params;
    tick = 0;
    tickLimit = _tickLimit;
    ticksPerSecond = _ticksPerSecond; 

    Worker* worker;
    worker = new Worker(5);
    HandTool* pick = new HandTool(1, "Pickaxe");
    worker->equippedTool = pick;
    worker->isToolEquipped = true;
    workers.push_back(worker);
}

// moves the game forward in time, and calls mine() on all miners. Is called in main() loop;
void Game::nextTick(){ 
    int len = workers.size();
    double mined = 0;

    for(int i=0; i<len; i++){
        mined += workers[i]->mine();
    }

    score += mined;
    gold += mined;
    goldMined.push_back(mined);
    scores.push_back(score);
    goldHistory.push_back(gold);
    tick++;
}

int Game::day(){ // returns day passed (24 ticks is one day)
    return floor(tick / 24.0);
}

void Game::powerCurrentTools(){
    if (gold >= 100) {
        gold = gold - 100;
        for (int i = 0;i < workers.size();i++) {
            workers[i]->equippedTool->setPowered();
        }
    }
}


Game::~Game(){
    workers.clear();
}

