#include "Tool.h"
#include "PowerTool.h"
#include "HandTool.h"
#include "MegaDrill.h"
#include "Worker.h"
#include "ItemShop.h"

#include <string>
#include <vector>

//moves item from shop to worker
void ItemShop::buyItem(int positionInShop, Worker *workerEquipping){
    workerEquipping->equippedTool = toolList[positionInShop];  //user will input number in shop e.g. 3, 
                                                                //3rd item in shop will be bough and added to desired worker
    workerEquipping->isToolEquipped = 1;
    toolList.erase (toolList.begin() + positionInShop -1);      //removes tool from this position in the shop
    numberOfTools--;
}
void ItemShop::addToItemShop(Tool * addedTool){
    toolList.push_back(addedTool);                              //adds tool to the item shop
    numberOfTools++;                                            //increments number of tools in shop by 1 for tracking size of shop
}
ItemShop::ItemShop(){
    vector<Tool *> toolList;
    numberOfTools = 0;
}