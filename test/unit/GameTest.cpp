#include "../../src/Game.h"
#include "../../src/Worker.h"
#include "../../src/HandTool.h"

// mocks
#include "../../src/testing/MockWorker.h"

#include "gtest/gtest.h"
#include <chrono>
#include <thread>

using testing::Return;

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
    EXPECT_TRUE(instanceof<Worker>(game.workers[0])) << "there is no worker at tick 0" << std::endl;
}

TEST(TestGameInstance, nextTick){

    MockWorker w = MockWorker(5, 0);
    // mining rate of 1
    EXPECT_CALL(w, mine()).WillRepeatedly(Return(1));
    // TODO: this is bad should probably write a TestWorker ey?
    game.workers[0] = &w;

    int len = game.workers.size();

    // run game for 50 ticks -> ~2 days
    int ticks = 50;
    for(int i=0; i<ticks; i++){
        game.nextTick(1);
        EXPECT_EQ(game.goldMined[i], 1) << "Incorrect amount gold mined per tick" << std::endl;
        EXPECT_EQ(game.scores[i], i + 1) << "Incorrect score history" << std::endl;
        EXPECT_EQ(game.goldHistory[i], i + 1) << "Incorrect gold balance history" << std::endl;
    }

    EXPECT_EQ(game.gold, len * ticks) << "Final gold mined is incorrect" << std::endl;
    EXPECT_EQ(game.score, len * ticks) << "Final score is incorrect" << std::endl;
    EXPECT_EQ(game.tick, 50) << "Day is incorrect" << std::endl;
    EXPECT_EQ(game.day(), 2) << "Day is incorrect" << std::endl;
}

TEST(TestGameInstance, updateFail){
    bool updated = game.update();
    EXPECT_FALSE(updated) << "Game should not update" << std::endl;
}

TEST(TestGameInstance, updatePass){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bool updated = game.update();
    EXPECT_TRUE(updated) << "Game should update" << std::endl;
}


TEST(TestGameInstance, getTotalMiningRate){
    MockWorker w = MockWorker(5, 0);
    // mining rate of 5
    EXPECT_CALL(w, mine()).WillRepeatedly(Return(5));
    game.workers[0] = &w;
    EXPECT_EQ(5, game.getTotalMiningRate());
}

// the following tests do not use mocks
TEST(TestGameInstance, buyWorker){
    EXPECT_EQ(1, game.workers.size());
    int price = game.workerPrice;
    game.gold = 10;
    bool bought = game.buyWorker();
    EXPECT_TRUE(bought) << "Couldn't buy worker" << std::endl;
    EXPECT_EQ(0, game.gold) << "Did not update gold amount to amount required" << std::endl;
    EXPECT_EQ(2, game.workers.size());
    // EXPECT_TRUE(instanceof<Worker>(game.workers[1])) << "No worker was added to the game after buying" << std::endl;
    EXPECT_EQ(price * 2, game.workerPrice) << "Price of next worker was not increased by 2x" << std::endl;
}


TEST(TestGameInstance, checkWorkersToUpgrade){
    EXPECT_EQ(1, game.workers.size());
    // check workers to upgrade
    game.checkWorkersToUpgrade();
    EXPECT_EQ(1, game.workersToUpgrade) << "number of upgraded workers not updated properly";
}