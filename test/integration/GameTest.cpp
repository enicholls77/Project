#include "../../src/Game.h"

#include "gtest/gtest.h"


// tests if game default initial settings
TEST(TestGameInstance, GameTicksPerSecond){
    const Game game = Game();

    EXPECT_EQ(0, game.tick) << "initial tick is 0";
    EXPECT_EQ(1, game.ticksPerSecond) << "tps is 1";
    EXPECT_EQ(2400, game.tickLimit) << "tick limit is 2400 ticks";
}
