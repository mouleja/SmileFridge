/******************************************************************************
** Program name: SmileFridge.cpp
** Authors: Jason Moule & Tommy Armstrong
** CS361-400-W20
** Date: 1/30/20
** Description: Spike driver for data investigation
******************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "User.hpp"
#include "Items.hpp"
#include "Fridge.hpp"

// Prototypes

// Main
int main()
{
    cout << endl << "Welcome to your SmileFridge!!!" << endl << endl;

    Fridge* fridge = new Fridge();
    User* user = fridge->GetUser();
    map<string, ItemInfo*> items = fridge->GetAllItems();
    vector<FridgeItem*> contents = fridge->GetContents();
    
    cout << "Printing fridge contents:" << endl << endl;

	cout << "displayName| fullName| sku| dateDay, dateYear| quantity| order quantity | goodFor| favorite";
	cout << endl << endl;
	for (FridgeItem* i : contents)
    {
        ItemInfo* item = i->itemInfo;
        cout << item->displayName << "| " << item->fullName << "| " << item->sku << "| ";
        cout << i->dateDay << ", " << i->dateYear << "| " << i->quantity << "| " << item->orderQuantity << "|" << i->goodFor;
        if (item->favorite) cout << "| Favorite";
        cout << endl;
    }

	cout << endl << "Printing fridge favorites:" << endl << endl;

    map<string, ItemInfo*>::iterator it = items.begin();
	while (it != items.end())
	{
        ItemInfo* item = it->second;
        if (item->favorite)
        {
            int fridgeIndex = fridge->GetIndexBySku(item->sku);
            int quantInFridge = 0;
            if (fridgeIndex > -1)
            {
                quantInFridge = contents[fridgeIndex]->quantity;
            }
            cout << item->displayName << " - ";
            if (quantInFridge)
            {
                cout << quantInFridge;
            }
            else
            {
                cout << "None";
            }
            cout << " in fridge." << endl << endl;
        }
        ++it;
	}

	cout << "Ordering Low Items" << endl;
	fridge->orderLowItems();
	fridge->printOrderList();
	cout << "Placing Order" << endl;
	fridge->placeOrder();
	cout << "Updating Inventory" << endl;
	fridge->updateInventory();
    return 0;
} //End Main

