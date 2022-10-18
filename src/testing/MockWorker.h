#ifndef MOCKWORKER_H
#define MOCKWORKER_H

#include <gmock/gmock.h>

#include "../Worker.h"
#include "../Tool.h"
#include <string>
using namespace std;

class MockWorker : public Worker{
   
    public:
    MockWorker(int _price, int _id): Worker(_price, _id){
        price = _price;
        id = _id;
    }
    MOCK_METHOD(double, mine, (), (override)); // returns gold mined in one tick

};

#endif 