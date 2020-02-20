/******************************************************************************
** Program name: SmileFridge.cpp
** Authors: Jason Moule & Tommy Armstrong & Ryan Jones
** CS361-400-W20
** Date: 02/09/20
** Description: Updated main file for running/testing User Story 1 (add and
**              remove inventory items)
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
#include <cstdlib>

#include "iohelper.hpp"
#include "Fridge.hpp"
#include "climateEntry.h"
#include "climateControl.h"

// Prototypes

// Main
int main()
{
    srand((unsigned int)time(NULL));
    //Creating menu strings


    int menuChoice = -1;
    int accountChoice;
    string userName, orderJson;
    string userPassword;
    string userEmail;
    string welcomeMessage = "Welcome to the SmileFridge app!!!\n\n";
    string accountString = "You must log in or create a new account to proceed\n"
                            "1. Log into existing account\n"
                            "2. Create new account\n"
                            "Please enter your choice:";
    string enterNameString = "Please enter a name:";
    string nameError = "Your name cannot be blank. Please try again:";
    string enterEmailString = "Please enter an email address:";
    string emailError = "Your email cannot be blank or contain spaces and must be in the form email@something.com. Please try again:";
    string enterPasswordString = "Please enter a password:";
    string passwordError = "Your password cannot be blank or contain spaces. Please try again:";
    string menuString = "\n\nWhat would you like to do?\n"
                        "1. Show SmileFridge contents\n"
                        "2. Show My Favorites\n"
                        "3. Add New Item to my SmileFridge\n"
                        "4. Remove Item from my SmileFridge\n"
                        "5. Update Quantity of an existing item\n"
                        "6. View SmileFridge Climate control\n"
                        "7. Update Order List and view\n"
                        "8. Receive a shipped order\n"
                        "0. Quit the SmileFridge app\n\n"
                        "Please enter your choice:";
    //Initialize climate object to access climate objects.
    climateControl* cC;

    cC = new climateControl;

    //Introducing the program and asking the user to log in or create account
    cout << welcomeMessage;
    accountChoice = getInt(1, 2, accountString);

    //Asking user for log in information or account creation information
    userName = getNonEmptyString(enterNameString, nameError);
    userEmail = getNonEmptyNoSpacesString(enterEmailString, emailError);
    userPassword = getNonEmptyNoSpacesString(enterPasswordString, passwordError);


    //Creating new User object
    User* newUser = new User(userName, userEmail, userPassword);;

    if (accountChoice == 1)
    {
        newUser->findAccountNumber();
    }
    else
    {
        newUser->createAccount();
    }

    Fridge* fridge = new Fridge(newUser);
    map<string, ItemInfo*> items = fridge->GetAllItems();
    vector<FridgeItem*> contents = fridge->GetContents();
    vector<ItemInfo*> favorites = fridge->GetFavorites();

//    climateControl cC;
//    cC.climateMenu();

    //Menu loop for user to navigate the app
    while (menuChoice != 0)
    {
        //Displaying menu and asking user what they would like to do
        menuChoice = getInt(0, 8, menuString);


        //Case statement based on user's menu choice
        switch (menuChoice)
        {
        case 1: //Show user's SmileFridge Contents
            cout << "Printing fridge contents:" << endl << endl;

            for (FridgeItem* i : contents)
            {
                ItemInfo* item = i->itemInfo;
                cout << item->displayName << "| " << item->fullName << "| " << item->sku << "| ";
				cout << GetDateString(i->dateStocked) << "| " << i->quantity << "| " << i->quantOnOrder;
                if (item->favorite) cout << "| Favorite";
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

            break;
        case 6: //get Climate control info.

            cC->climateMenu();

            break;
        case 7: //Update orderList and print contents
            fridge->orderLowItems();
            fridge->printOrderList();
            fridge->SubmitOrder();
			contents = fridge->GetContents(); //update vector associated with fridge contents
            break;
        case 8:
            printString();
            orderJson = getString("Enter order filename: ");
            fridge->ReceiveOrder(orderJson);
			contents = fridge->GetContents(); //update vector associated with fridge contents
            break;
        case 0: //Quit the SmileFridge app
            cout << "\nThanks for using the SmileFridge app! Goodbye." << endl;
            break;
        default: 
            cout << "Invalid choice!  Try again." << endl << endl;
            menuChoice = getInt(0, 7, menuString);
        }
    }

    //Deleting user dynamic memory
    delete newUser;



    return 0;
} //End Main

