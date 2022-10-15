#include <cmath>

#include "Worker.h"
#include "Game.h"

using namespace std;

// default constructor
Game::Game(){
    currentDay = 0;
    tick = 0;
    tickLimit = 2400;
    ticksPerSecond = 1; 

    Worker* worker;
    worker = new Worker(5);
    workers.push_back(worker);
}

Game::Game(int _tickLimit, int _ticksPerSecond){ // constructor for setting custom params;
    tick = 0;
    tickLimit = _tickLimit;
    ticksPerSecond = _ticksPerSecond; 
}

void Game::nextTick(){ // moves the game forward in time, and calls mine() on all miners. Is called in main() loop;
    int len = workers.size();
    int mined = 0;

    for(int i=0; i<len; i++){
        mined += workers[i]->mine();
    }

    score += mined;
    gold += mined;
    goldMined.push_back(mined);
    scores.push_back(score);
}

int Game::day(){ // returns day passed (24 ticks is one day)
    return floor(tick / 24);
}

void Game::powerCurrentTools(){
    for (int i = 0;i < workers.size();i++) {
        workers[i]->equippedTool->setPowered();
    }
}


Game::~Game(){
    workers.clear();
}

