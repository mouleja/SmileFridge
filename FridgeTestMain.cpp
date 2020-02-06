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

#include <string>
using std::string;

#include <iomanip>
#include <fstream>
#include <sstream>

#include "User.hpp"
#include "Item.hpp"
#include "Inventory.hpp"
#include "Fridge.hpp"

// Prototypes

// Main
int main()
{
    cout << endl << "Welcome to your SmileFridge!!!" << endl << endl;

    User *user = new User("Joe Blow", "joe@blow.com", "AFE87WE34FES");
    Fridge *fridge = new Fridge(user);
    map<Item*, int> contents = fridge->GetContents();
	map<Item*, int> favorites = fridge->GetFavorites();

    cout << "Printing fridge contents:" << endl << endl;

	Item* item;
	for (map<Item*, int>::iterator it = contents.begin(); it != contents.end(); it++)
    {
		item = it->first;
        cout << item->GetDisplayName() << "| " << item->GetFullName() << "| " << item->GetSku() << "| ";
        cout << item->GetDate() << "| " << it->second << "| " << item->GetOrderPoint();
        if (item->IsFavorite()) cout << "| Favorite";
        cout << endl;
    }

	cout << endl << "Printing fridge favorites:" << endl << endl;

	for (map<Item*, int>::iterator it = favorites.begin(); it != favorites.end(); it++)
	{
		item = it->first;
		cout << item->GetDisplayName() << "| " << item->GetFullName() << "| " << item->GetSku() << "| ";
		cout << item->GetDate() << "| " << it->second << "| " << item->GetOrderPoint() << endl;
	}

    return 0;
} //End Main

