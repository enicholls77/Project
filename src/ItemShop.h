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
    //moves item from shop to worker
    void buyItem(int positionInShop, Worker *workerEquipping);
    //will print name, price, power required, and mining rate of each tool, and position in shop. Depends on UI implementation.
    void printShop();
};
#endif