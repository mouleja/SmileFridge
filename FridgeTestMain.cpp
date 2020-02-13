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

#include "User.hpp"
#include "Item.hpp"
#include "Inventory.hpp"
#include "iohelper.hpp"

// Prototypes

// Main
int main()
{
    //Creating menu strings
    int menuChoice = 0;
    int accountChoice;
    string userName;
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
                        "6. Quit the SmileFridge app\n\n"
                        "Please enter your choice:";
    

    //Introducing the program and asking the user to log in or create account
    cout << welcomeMessage;
    accountChoice = getInt(1, 2, accountString);

    //Asking user for log in information or account creation information
    userName = getNonEmptyString(enterNameString, nameError);
    userEmail = getNonEmptyNoSpacesString(enterEmailString, emailError);
    userPassword = getNonEmptyNoSpacesString(enterPasswordString, passwordError);
    

    //Creating new User object
    User* newUser = new User(userName, userEmail, userPassword);

    if (accountChoice == 1)
    {
        newUser->findAccountNumber();
    }
    else
    {
        newUser->createAccount();
    }


    //Temporary hard coded user information
    User* user = new User("Joe Blow", "joe@blow.com", "Password123456789"); //"AFE87WE34FES"
    Inventory* inventory = new Inventory();
    vector<Item*> contents = inventory->GetContents();
    vector<Item*> favorites = inventory->GetFavorites();

    
    //Menu loop for user to navigate the app
    while (menuChoice != 6)
    {
        //Displaying menu and asking user what they would like to do
        menuChoice = getInt(1, 6, menuString);


        //Case statement based on user's menu choice
        switch (menuChoice)
        {
        case 1: //Show user's SmileFridge Contents
            cout << "Printing fridge contents:" << endl << endl;

            for (Item* item : contents)
            {
                cout << item->GetDisplayName() << "| " << item->GetFullName() << "| " << item->GetSku() << "| ";
                cout << item->GetDate() << "| " << item->GetQuantity() << "| " << item->GetOrderPoint();
                if (item->IsFavorite()) cout << "| Favorite";
                cout << endl;
            }

            break;
        case 2: //Show user's favorites
            cout << endl << "Printing fridge favorites:" << endl << endl;

            for (Item* item : favorites)
            {
                cout << item->GetDisplayName() << "| " << item->GetFullName() << "| " << item->GetSku() << "| ";
                cout << item->GetDate() << "| " << item->GetQuantity() << "| " << item->GetOrderPoint() << endl;
            }

            break;
        case 3: //Add New Item to user's SmileFridge

            break;
        case 4: //Remove Item from user's SmileFridge

            break;
        case 5: //Update Quantity of an existing item

            break;
        case 6: //Quit the SmileFridge app
            cout << "\nThanks for using the SmileFridge app! Goodbye.";
        }
    }
    
    //Deleting user dynamic memory
    delete newUser;



    return 0;
} //End Main

