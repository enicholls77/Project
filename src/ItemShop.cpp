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
void ItemShop::printShop(){
    //will print name, price, power required, and mining rate of each tool, and position in shop. Depends on UI implementation.
}