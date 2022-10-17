#include <cmath>
#include <iostream>
#include <algorithm>

#include "Worker.h"
#include "Tool.h"
#include "HandTool.h"
#include "PowerTool.h"
#include "MegaDrill.h"
#include "ItemShop.h"
#include "Game.h"
#include <vector>
#include <chrono>
#include <string>

using namespace std;

// default constructor
Game::Game(){
    tick = 0;
    tickLimit = 2400;
    ticksPerSecond = 1; 
    gold = 0;
    score = 0;
    workersToUpgrade = 1;
    upgradeAllBasePrice = 100;
    poweringBasePrice = 100;
    workerPrice = 10;
    powerSupplied = 0;
    powerSuppliedTickLength = 24;
    powerableTools = 0;
    scores = new double[2400]{0};   //need to make sure ticklimit isn't set too large

    //adding tools to game
    HandTool *stonePick = new HandTool(1.5, "Stone Pick.", 10);
    HandTool *ironPick = new HandTool(2, "Iron Pick.", 50);
    HandTool *carbonPick = new HandTool(3, "Carbon Fibre Pick.", 100);
    PowerTool *steelDrill = new PowerTool(2, "Steel Drill", 4, 200);
    PowerTool *diamondDrill = new PowerTool(2, "Diamond Drill", 8, 300);
    MegaDrill *megaDrill = new MegaDrill(4, "Mega Drill", 16, 500);
    MegaDrill *diamondMegaDrill = new MegaDrill(4, "Diamond Mega Drill", 46, 1000);

    // adding items to shop
    addTool(stonePick);
    addTool(ironPick);
    addTool(carbonPick);
    addTool(steelDrill);
    addTool(diamondDrill);
    addTool(megaDrill);
    addTool(diamondMegaDrill);

    Worker* worker;
    worker = new Worker(5);
    HandTool* pick = new HandTool(1, "Pickaxe", 1);
    worker->equippedTool = pick;
    worker->isToolEquipped = true;
    workers.push_back(worker);
    checkWorkersToUpgrade();
    

    // startingTime = std::clock();
    startingTime = std::chrono::steady_clock::now();
    timeElapsed = 0;
}

Game::Game(int _tickLimit, int _ticksPerSecond){ // constructor for setting custom params;
    tick = 0;
    tickLimit = _tickLimit;
    ticksPerSecond = _ticksPerSecond; 
    gold = 0;
    score = 0;
    workersToUpgrade = 1;
    upgradeAllBasePrice = 100;
    poweringBasePrice = 100;
    workerPrice = 10;
    powerSupplied = 0;
    powerSuppliedTickLength = 24;
    powerableTools = 0;
    scores = new double[_tickLimit]{0};   //need to make sure ticklimit isn't set too large

    // tools
    HandTool *stonePick = new HandTool(1.5, "Stone Pick.", 10);
    HandTool *ironPick = new HandTool(2, "Iron Pick.", 5);
    HandTool *carbonPick = new HandTool(3, "Carbon Fibre Pick.", 1);
    PowerTool *steelDrill = new PowerTool(2, "Steel Drill", 4, 2);
    PowerTool *diamondDrill = new PowerTool(2, "Diamond Drill", 8, 3);
    MegaDrill *megaDrill = new MegaDrill(4, "Mega Drill", 16, 5);
    MegaDrill *diamondMegaDrill = new MegaDrill(4, "Diamond Mega Drill", 46, 10);

    // adding items to shop
    addTool(stonePick);
    addTool(ironPick);
    addTool(carbonPick);
    addTool(steelDrill);
    addTool(diamondDrill);
    addTool(megaDrill);
    addTool(diamondMegaDrill);

    Worker* worker;
    worker = new Worker(5);
    HandTool* pick = new HandTool(1, "Worn Pick.", 1);
    worker->equippedTool = pick;
    worker->isToolEquipped = true;
    workers.push_back(worker);
    checkWorkersToUpgrade();

    startingTime = std::chrono::steady_clock::now();
    timeElapsed = 0;
}

// updates game state
bool Game::update(){ 
    clock_t currentTime = std::clock();
    // timeElapsed = double(currentTime - startingTime) / CLOCKS_PER_SEC;
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startingTime).count();
    int tickDelta = floor(timeElapsed * ticksPerSecond) - tick;
    if (tickDelta >= 1){
        nextTick(false);
        return true;
    }
    return false;
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
    checkWorkersToUpgrade();
    checkPowerableTools();
    if(poweringFor>0){
        poweringFor--;  //deincrements powerFor by 1 every tick while it is above 0
        if (poweringFor == 0){ //once poweringFor has become zero, power down all tools (Maybe add UI log message?)
            for(int i = 0; i < workers.size(); i++){ 
                workers[i]->equippedTool->setUnPowered();
            }
        }
    }
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

void Game::clearScores(){
    delete[] scores;
}

bool Game::buyWorker(){
    if(workerPrice > gold){
        return false;
    }
    Worker* newWorker;
    newWorker = new Worker(5);
    HandTool* pick = new HandTool(1, "Pickaxe", 1);
    newWorker->equippedTool = pick;
    newWorker->isToolEquipped = true;
    gold -= workerPrice;
    workers.push_back(newWorker);
    workerPrice = workerPrice * 2;
    return true;
}

Game::~Game(){
    workers.clear();
    workerShop.clear();
    delete[] scores;
}

bool Game::buyTool(int positionInShop){
    double price = toolShop[positionInShop]->price;
    if(price > gold){
        return false;
    }
    // sorts workers - ascending by mining rate
    std::sort( workers.begin(), workers.end(), []( Worker* a, Worker* b ) -> bool 
        { 
            return (bool)(a->mine() < b->mine()); 
        } 
    );
    gold -= price;
    Worker* workerEquipping = workers[0];

    workerEquipping->equippedTool = toolShop[positionInShop];
    toolShop.erase(toolShop.begin() + positionInShop);
    return true;
}

void Game::addTool(Tool *toolAdded){
    toolShop.push_back(toolAdded);
}

bool Game::upgradeAll(){
    if (upgradeAllBasePrice*workersToUpgrade > gold) {
        return false;
    }
    else {
        gold -= upgradeAllBasePrice*workersToUpgrade;
        for (int j = 0; j < workers.size(); j++){
            workers[j]->equippedTool->upgrade();
        }
        return true;
    }
}

void Game::checkWorkersToUpgrade(){
    workersToUpgrade = 0;
    for (int i = 0; i < workers.size(); i++){
        if (workers[i]->equippedTool->upgraded == false){
            workersToUpgrade++;
        }
    }
}

void Game::checkPowerableTools(){
    powerableTools = 0;
    for (int i = 0; i < workers.size(); i++){
        if (workers[i]->equippedTool->powerTool == true){
            powerableTools++;
        }
    }
}

bool Game::powerCurrentTools(){
    if (gold >= poweringBasePrice * powerableTools) {
        gold = gold - poweringBasePrice * powerableTools;
        for (int i = 0;i < workers.size();i++) {
            workers[i]->equippedTool->setPowered();
        }
        poweringFor = powerSuppliedTickLength;
        return true;
    }
    return false;
}