#include "../../src/Worker.h"
#include "../../src/HandTool.h"
#include "../../src/testing/MockHandTool.h"

#include "gtest/gtest.h"

using testing::Return;
namespace {

Worker worker = Worker(5, 0);

// mock testing 
TEST(TestWorkerInstance, Setup){
    MockHandTool mockTool = MockHandTool(1, "MockTool", 69);
    EXPECT_EQ(1, worker.mine()) << "miningRate incorrect before tool equipped" << std::endl;
    worker.equippedTool = &mockTool;
    worker.isToolEquipped = true;
    EXPECT_CALL(mockTool, getMiningMultiplier()).WillRepeatedly(Return(5));
    EXPECT_EQ(5, worker.mine()) << "miningRate incorrect after tool equipped" << std::endl;
}

}