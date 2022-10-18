#ifndef GAME_H
#define GAME_H

#include "Worker.h"
#include "Tool.h"
#include "HandTool.h"
#include "PowerTool.h"
#include "MegaDrill.h"
#include <vector>
#include <chrono>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

class Game{
   
    public:
    Game(); // default constructor;
    Game(int _tickLimit, int _ticksPerSecond); // constructor for setting custom params and debugging;
    int tick = 0; // one tick is 1 hr in game;
    int tickLimit = 2400; // max game length in ticks;
    int ticksPerSecond = 1; // ticks per second 
    int nextId = 0;
    std::chrono::steady_clock::time_point startingTime;
    double timeElapsed;
    double score; // game score, cumulative gold collected from mining 
    double gold; // gold available to spend
    double upgradeAllBasePrice = 100; //price to upgrade all tools
    double poweringBasePrice; //price to supply power per powerable unit
    int workersToUpgrade; //number of unupgraded workers
    double workerPrice; //price of new worker, doubles for every worker bought
    bool powerSupplied; //tells if the Powered boost is enabled
    int powerableTools; //tells number of powerable tools   
    int powerSuppliedTickLength; //number of ticks power should be supplied for
    int poweringFor; //number of ticks left before unpowering tools
    vector<Worker*> workers; //vector containing all active workers
    vector<Worker*> workerShop; //vector containing purchaseable workers
    vector<Tool *> toolShop; //
    //ItemShop *toolShop;
    vector<double> goldMined; // gold mined per tick
    vector<double> goldHistory; // gold balance history 
    //vector<double> scores; // score history
    vector<double> scores; //score history
    bool update();
    void nextTick(int _ticksPassed); // moves the game forward in time, and calls mine() on all miners. Is called in main() loop;
    double getTotalMiningRate(); // gold per tick
    // bool isPaused; game pause?
    int day(); // returns days passed since game started (24 ticks is one day)
    ~Game(); // destructor
    bool powerCurrentTools(); //gives power to all tools currently equipped. Must be rebought if new tools are bought.
    bool buyWorker(); //buys a new worker
    bool buyTool(int positionInShop, Worker* workerEquipping); //buying an tool from the tool shop
    void addTool(Tool *toolAdded); //adding a tool to the tool shop
    bool upgradeAll(); //upgrades tools of all workers
    void checkWorkersToUpgrade(); //checks number of workers to upgrade
    void checkPowerableTools(); //checks number of powerable tools
};

#endif //GAME_H