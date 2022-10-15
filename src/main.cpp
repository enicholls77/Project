#include <string.h>
#include <vector>
#include <iostream>

#include "Game.h"

using namespace std;

// main game loop
int main() {
    cout << "helloooo" << endl;
    Game g = Game();
    cout << g.tick << endl;
    cout << g.ticksPerSecond << endl;
    cout << g.tickLimit << endl;

    return 0;
}




