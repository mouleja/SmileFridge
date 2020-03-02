/******************************************************************************
** Program name: SmileFridge.cpp
** Authors: Jason Moule & Tommy Armstrong & Ryan Jones
** CS361-400-W20
** Date: 02/09/20
** Description: Main file for executing SmileFridge application
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


#include "iohelper.hpp"
#include "Fridge.hpp"
#include "climateEntry.h"
#include "climateControl.h"


// Prototypes
long int findAccountNumber(string userName, string userEmail, string userPassword);

// Main
int main()
{
    //Creating menu strings

    int menuChoice = 0;
    int accountChoice;
    int updateAmount;
    string updateSku;
    string welcomeMessage = "Welcome to the SmileFridge app!!!\n\n";
    string accountString = "You must log in or create a new account to proceed\n"
                            "1. Log into existing account\n"
                            "2. Create new account\n"
                            "Please enter your choice:";
    string menuString = "\n\nWhat would you like to do?\n"
                        "1. Show SmileFridge contents\n"
                        "2. Show My Favorites\n"
                        "3. Add New Item to my SmileFridge\n"
                        "4. Remove Item from my SmileFridge\n"
                        "5. Update Quantity of an existing item\n"
                        "6. View SmileFridge Climate control\n"
                        "7. Quit the SmileFridge app\n\n"
                        "Please enter your choice:";
    string enterSkuString = "Please enter the sku for which you would like to update the quantity of:";
    string skuError = "You cannot enter a SKU that is blank or has spaces. Please try again";
    string updateAmountString = "Please enter the new amount of your item in the fridge:";

    //Initialize climate object to access climate objects.
    climateControl* cC;

    cC = new climateControl;

    //Introducing the program and asking the user to log in or create account
    cout << welcomeMessage;
    accountChoice = getInt(1, 2, accountString);

    //Creating new User object
    User* newUser = new User();
    newUser->setUpAccount(accountChoice);

    //Creating Fridge objects and populating with user's inventory
    Fridge* fridge = new Fridge(newUser);
    map<string, ItemInfo*> items = fridge->GetAllItems();
    vector<FridgeItem*> contents = fridge->GetContents();
    vector<ItemInfo*> favorites = fridge->GetFavorites();



    //Menu loop for user to navigate the app
    while (menuChoice != 7)
    {
        //Displaying menu and asking user what they would like to do
        menuChoice = getInt(1, 7, menuString);

        system("CLS");
        cout << "\n" << flush;


        //Case statement based on user's menu choice
        switch (menuChoice)
        {
        case 1: //Show user's SmileFridge Contents
            cout << "Printing fridge contents:" << endl << endl;
            cout << "**********************************************************************************" << endl;
            cout << "|Item Name|Item SKU  |Fresh Until (day)|(year)|Quantity|Good For (days)|Favorite?|" << endl;
            cout << "**********************************************************************************" << endl;

            for (FridgeItem* i : contents)
            {
                ItemInfo* item = i->itemInfo;
                cout << "|" << left << setw(9) << item->displayName << "|" << left << setw(10) << item->sku << "|";
                cout << left << setw(17) << i->dateDay << "|" << left << setw(6) << i->dateYear << "|" << left << setw(8) << i->quantity << "|" << left << setw(15) << i->goodFor;
                if (item->favorite) cout << "|Favorite";
                cout << endl;
            }

            break;
        case 2: //Show user's favorites
            cout << endl << "Printing fridge favorites:" << endl << endl;

            for (ItemInfo* item : favorites)
            {
                cout << item->displayName << "| (" << item->sku << ")| ";
                FridgeItem* current = fridge->GetInfoBySku(item->sku);
                if (current != nullptr && current->quantity > 0)
                {
                    cout << current->quantity;
                }
                else
                {
                    cout << "None";
                }
                cout << " in the fridge." << endl << endl;
            }
            break;
        case 3: //Add New Item to user's SmileFridge

            break;
        case 4: //Remove Item from user's SmileFridge

            break;
        case 5: //Update Quantity of an existing item
          
            updateSku = getNonEmptyNoSpacesString(enterSkuString, skuError);
            updateAmount = getInt(0, 100, updateAmountString);
            fridge->Update(updateSku, updateAmount);
            break;
        case 6: //get Climate control info.

            cC->climateMenu();

            break;
        case 7: //Quit the SmileFridge app
            cout << "\nThanks for using the SmileFridge app! Goodbye.";
        }
    }

    //Deleting user dynamic memory
    delete newUser;


    return 0;
} //End Main