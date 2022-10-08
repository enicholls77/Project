#ifndef GAME_H
#define GAME_H

#include "Worker.h"
using namespace std;

class Game{
   
    public:
    Game(); // default constructor;
    Game(int _tickLimit, int _ticksPerSecond); // constructor for setting custom params and debugging;
    int tick; // one tick is 1 hr in game;
    int tickLimit; // max game length in ticks;
    int ticksPerSecond; // ticks per second 
    int score; // game score, cumulative gold collected from mining 
    int gold; // gold available to spend
    void nextTick(); // moves the game forward in time, and calls mine() on all miners. Is called in main() loop;
    // bool isPaused; game pause?
    int day(); // returns days passed since game started (24 ticks is one day)

};

#endif GAME_H