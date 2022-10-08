#include "Worker.h"
#include "Game.h"
#include <math.h>

using namespace std;

// default constructor
Game::Game(){
    tick = 0;
    tickLimit = 2400;
    ticksPerSecond = 1; 
}

Game::Game(int _tickLimit, int _ticksPerSecond){ // constructor for setting custom params;
    tick = 0;
    tickLimit = _tickLimit;
    ticksPerSecond = _ticksPerSecond; 
}
void Game::nextTick(){ // moves the game forward in time, and calls mine() on all miners. Is called in main() loop;
}

int Game::day(){ // returns day passed (24 ticks is one day)
    return floor(tick / 24);
}