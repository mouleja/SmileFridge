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
//#include "Inventory.hpp"
#include "Fridge.hpp"
#include "DateConverter.hpp"

// Prototypes

// Main
int main()
{
    cout << endl << "Welcome to your SmileFridge!!!" << endl << endl;
    /*
    Fridge* fridge = new Fridge();
    User* user = fridge->GetUser();
    map<string, ItemInfo*> items = fridge->GetAllItems();
    vector<FridgeItem*> contents = fridge->GetContents();
    
    cout << "Printing fridge contents:" << endl << endl;

	for (FridgeItem* i : contents)
    {
        ItemInfo* item = i->itemInfo;
        cout << "displayName| fullName| sku| dateDay, dateYear| quantity| goodFor| favorite";
        cout << endl << endl;
        cout << item->displayName << "| " << item->fullName << "| " << item->sku << "| ";
        cout << i->dateDay << ", " << i->dateYear << "| " << i->quantity << "| " << i->goodFor;
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
    */

    Date today = GetCurrentDate();
    Date date1 = MakeDate(12, 25, 2016);
    cout << "Today is day number " << today.Days << " of " << today.Year << endl;
    cout << "It has been " << GetDaysBetween(today, date1) << " days since 12/25/2016." << endl;
    
    int day1 = 1, month1 = 1, year1 = 1900, day2 = 1, month2 = 1, year2 = 1900;
    cout << "Enter 2 dates:" << endl;
    cout << "[First day (1-31)] [First Month(1-12)] [First Year(1900-2900)] e.g.: 12 25 2019" << endl;
    cin >> day1 >> month1 >> year1;
    cout << "[Second day (1-31)] [Second Month(1-12)] [Second Year(1900-2900)] e.g.: 2 11 2020" << endl;
    cin >> day2 >> month2 >> year2;

    Date first = MakeDate(day1, month1, year1);
    Date second = MakeDate(day2, month2, year2);
    cout << "There are " << GetDaysBetween(first, second) << " days between the two dates.";
    int diff = CompareDates(first, second);
    if (diff == -1) cout << "  The first date is earlier.";
    else if (diff == 0) cout << "  The dates are the same.";
    else cout << "  The first date is later.";
    cout << endl << endl;

    cout << "90 days after 11/15/2019 is ";
     date1 = MakeDate(11, 15, 2019);
    date1 = AddDaysToDate(date1, 90);
    cout << GetDateString(date1) << endl;

    cout << "The Date format of that result is: ";
    GetDateInts(date1, &year1, &day1);
    cout << "(" << year1 << ", " << day1 << ")" << endl;

    return 0;
 } //End Main

