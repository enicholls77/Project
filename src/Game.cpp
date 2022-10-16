#include <cmath>
#include <iostream>

#include "Worker.h"
#include "Tool.h"
#include "HandTool.h"
#include "PowerTool.h"
#include "MegaDrill.h"
#include "ItemShop.h"
#include "Game.h"
#include <vector>
#include <ctime>
#include <string>

using namespace std;

// default constructor
Game::Game(){
    tick = 0;
    tickLimit = 2400;
    ticksPerSecond = 1; 
    gold = 0;
    score = 0;
    scores = new double[2400]{0};   //need to make sure ticklimit isn't set too large

    toolShop = new ItemShop();
    Worker* worker;
    worker = new Worker(5);
    HandTool* pick = new HandTool(1, "Pickaxe");
    worker->equippedTool = pick;
    worker->isToolEquipped = true;
    workers.push_back(worker);

    startingTime = std::clock();
    timeElapsed = 0;
}

Game::Game(int _tickLimit, int _ticksPerSecond){ // constructor for setting custom params;
    tick = 0;
    tickLimit = _tickLimit;
    ticksPerSecond = _ticksPerSecond; 
    gold = 0;
    score = 0;
    scores = new double[_tickLimit]{0};   //need to make sure ticklimit isn't set too large

    ItemShop *toolShop = new ItemShop();
    Worker* worker;
    worker = new Worker(5);
    HandTool* pick = new HandTool(1, "Pickaxe");
    worker->equippedTool = pick;
    worker->isToolEquipped = true;
    workers.push_back(worker);

    startingTime = std::clock();
    timeElapsed = 0;
}

// updates game state
void Game::update(){ 
    clock_t currentTime = std::clock();
    timeElapsed = double(currentTime - startingTime) / CLOCKS_PER_SEC;
    int tickDelta = floor(timeElapsed * ticksPerSecond) - tick;
    if (tickDelta >= 1){
        nextTick(false);
    }
}

// moves the game forward in time, and calls mine() on all miners. Is called in main() loop;
void Game::nextTick(bool _manual){ 
    int len = workers.size();
    double mined = getTotalMiningRate();

    score += mined;
    gold += mined;
    goldMined.push_back(mined);
    //scores.push_back(score);      //commenting out to use dynamically allocated array instead of vector
    scores[tick] = score;           //allocated score value as 
    goldHistory.push_back(gold);
    // TODO: Yuck
    if(!_manual){
        int tickDelta = floor(timeElapsed * ticksPerSecond) - tick;
        tick += tickDelta;
    } else{
        tick++;
    }
}

int Game::day(){ // returns day passed (24 ticks is one day)
    return floor(tick / 24.0);
}

// returns gold per tick
double Game::getTotalMiningRate(){
    int len = workers.size();
    double gPerTick = 0;
    for(int i=0; i<len; i++){
        gPerTick += workers[i]->mine();
    }

    return gPerTick;
}

void Game::powerCurrentTools(){
    if (gold >= 100) {
        gold = gold - 100;
        for (int i = 0;i < workers.size();i++) {
            workers[i]->equippedTool->setPowered();
        }
    }
}

void Game::clearScores(){
    delete[] scores;
}

void Game::buyWorker(){
    Worker* newWorker;
    newWorker = new Worker(5);
    HandTool* pick = new HandTool(1, "Pickaxe");
    newWorker->equippedTool = pick;
    newWorker->isToolEquipped = true;
    workers.push_back(newWorker);
}

Game::~Game(){
    workers.clear();
    workerShop.clear();
}

void Game::buyTool(int positionInShop, Worker *workerEquipping){
    toolShop->buyItem(positionInShop, workerEquipping);
}

void Game::addTool(Tool *toolAdded){
    toolShop->addToItemShop(toolAdded);
}