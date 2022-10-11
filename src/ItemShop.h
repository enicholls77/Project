#ifndef ITEMSHOP_H
#define ITEMSHOP_H

#include "Tool.h"
#include "PowerTool.h"
#include "HandTool.h"
#include "StonePickaxe.h"
#include "SteelPickaxe.h"
#include "SteelDrill.h"
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
    void buyItem(int positionInShop, Worker *workerEquipping){
        workerEquipping->equippedTool = toolList[positionInShop];  //user will input number in shop e.g. 3, 
                                                                    //3rd item in shop will be bough and added to desired worker
        workerEquipping->isToolEquipped = 1;
        toolList.erase (toolList.begin() + positionInShop -1);      //removes tool from this position in the shop
        numberOfTools--;
    }
    void printShop(){
        //will print name, price, power required, and mining rate of each tool, and position in shop. Depends on UI implementation.
    }
    



};
#endif