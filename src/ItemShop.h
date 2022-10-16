#ifndef ITEMSHOP_H
#define ITEMSHOP_H

#include "Tool.h"
#include "PowerTool.h"
#include "HandTool.h"
#include "MegaDrill.h"
#include "Worker.h"

#include <string>
#include <vector>

class ItemShop {
    private:
    vector<Tool *> toolList;    //vector of addresses to all tools in the shop
    int numberOfTools;          //number of tools in the shop total
    public:
    void buyItem(int positionInShop, Worker *workerEquipping); //moves item from shop to worker
    void addToItemShop(Tool * addedTool); //adding tool to shop
    ItemShop(); //basic constructor
};
#endif