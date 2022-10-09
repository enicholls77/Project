#ifndef GAME_H
#define GAME_H

#include "Worker.h"
#include <vector>
using namespace std;

class Game{
   
    public:
    Game(); // default constructor;
    Game(int _tickLimit, int _ticksPerSecond); // constructor for setting custom params and debugging;
    int tick = 0; // one tick is 1 hr in game;
    int tickLimit = 2400; // max game length in ticks;
    int ticksPerSecond = 1; // ticks per second 
    int score; // game score, cumulative gold collected from mining 
    int gold; // gold available to spend
    int currentDay;
    vector<Worker*> workers;
    vector<int> scores; // score per tick
    vector<int> goldMined; // gold mined per tick
    void nextTick(); // moves the game forward in time, and calls mine() on all miners. Is called in main() loop;
    // bool isPaused; game pause?
    int day(); // returns days passed since game started (24 ticks is one day)
    ~Game(); // destructor

};

#endif //GAME_H