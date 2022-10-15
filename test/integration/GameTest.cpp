#include "../../src/Game.h"
#include "../../src/Worker.h"

#include "gtest/gtest.h"

// checks if object is instance of a class type
template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

//game instance to use in some tests
Game game = Game();

// tests if game default initial settings
TEST(TestGameInstance, DefaultSettings){
    EXPECT_EQ(0, game.tick) << "initial tick is not 0" << std::endl;
    EXPECT_EQ(1, game.ticksPerSecond) << "tps is not 1" << std::endl;
    EXPECT_EQ(2400, game.tickLimit) << "tick limit is not 2400 ticks" << std::endl;
    EXPECT_TRUE(instanceof<Worker>(game.workers[0])) << "there is no worker at tick 0" << std::endl;
}

TEST(TestGameInstance, nextTick){
    game.nextTick();
}
