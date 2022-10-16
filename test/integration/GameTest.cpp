#include "../../src/Game.h"
#include "../../src/Worker.h"
#include "../../src/HandTool.h"

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

    int len = game.workers.size();

    for(int i=0; i<len; i++){
        EXPECT_EQ(game.workers[i]->equippedTool->getMiningMultiplier(), 1) << "Incorrect intial mining rate for starting worker(s)";
        // EXPECT_TRUE(game.workers[i]->equippedTool->returnToolName() == "Pickaxe") << std::endl;
    }
}

TEST(TestGameInstance, nextTick){
    int len = game.workers.size();

    // run game for 50 ticks -> ~2 days
    int ticks = 50;
    for(int i=0; i<ticks; i++){
        game.nextTick(true);
        EXPECT_EQ(game.goldMined[i], 1) << "Incorrect amount gold mined per tick" << std::endl;
        EXPECT_EQ(game.scores[i], i + 1) << "Incorrect score history" << std::endl;
        EXPECT_EQ(game.goldHistory[i], i + 1) << "Incorrect gold balance history" << std::endl;
    }

    EXPECT_EQ(game.gold, len * ticks) << "Final gold mined is incorrect" << std::endl;
    EXPECT_EQ(game.score, len * ticks) << "Final score is incorrect" << std::endl;
    EXPECT_EQ(game.tick, 50) << "Day is incorrect" << std::endl;
    EXPECT_EQ(game.day(), 2) << "Day is incorrect" << std::endl;
}


