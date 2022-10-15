#include <string.h>
#include <vector>
#include <iostream>

#include "Game.h"

using namespace std;

// main game loop
int main() {
    cout << "helloooo" << endl;
    Game g = Game();
    int len  = g.workers.size();

    cout << "len: " << len << endl;
    cout << g.tick << endl;
    cout << g.ticksPerSecond << endl;
    cout << g.tickLimit << endl;

    for(int i; i<51; i++){
        g.nextTick();
    }

    int day = g.day();
    cout << "day: " << day << endl;

    return 0;
}




