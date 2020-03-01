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

//#include "User.hpp"
//#include "Items.hpp"
//#include "Inventory.hpp"
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
    long int accountNumber = -1;
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
    string existingAccountError = "An account with that username already exists, please choose another";
    string noAccountError = "No account matches those credentials, please try again";
    string duplicateAccountError = "That account already exists, please choose new credentials";
    string duplicateEmailError = "That email is already linked to an account, please try again";
    string loginSuccess = "\nYou have been logged in successfully!";
    string accountCreationSuccess = "\nYou account has been successfully created!";
    string menuString = "\n\nWhat would you like to do?\n"
                        "1. Show SmileFridge contents\n"
                        "2. Show My Favorites\n"
                        "3. Add New Item to my SmileFridge\n"
                        "4. Remove Item from my SmileFridge\n"
                        "5. Update Quantity of an existing item\n"
                        "6. View SmileFridge Climate control\n"
                        "7. Quit the SmileFridge app\n\n"
                        "Please enter your choice:";

    //Initialize climate object to access climate objects.
    climateControl* cC;

    cC = new climateControl;

    //Introducing the program and asking the user to log in or create account
    cout << welcomeMessage;
    accountChoice = getInt(1, 2, accountString);
    bool foundAccount = false;


    /***Next section should probably be moved to User class...***/

    //Asking user to log in or create account
    if (accountChoice == 1) //Login
    {
        while (!foundAccount)
        {
            //Asking user for log in information
            userName = getNonEmptyString(enterNameString, nameError);
            userEmail = getNonEmptyNoSpacesString(enterEmailString, emailError);
            userPassword = getNonEmptyNoSpacesString(enterPasswordString, passwordError);
            accountNumber = findAccountNumber(userName, userEmail, userPassword);

            //Checking to see if account was found. If not, re-prompting user for credentials
            if (accountNumber > 0)
            {
                foundAccount = true;
                system("CLS");
                cout << loginSuccess << flush;
            }
            else
            {
                cout << noAccountError << endl;
            }
        }
    }
    else //Create account
    {
        foundAccount = true;
        while (foundAccount)
        {
            //Asking user for account creation information
            userName = getNonEmptyString(enterNameString, nameError);
            userEmail = getNonEmptyNoSpacesString(enterEmailString, emailError);
            userPassword = getNonEmptyNoSpacesString(enterPasswordString, passwordError);
            accountNumber = findAccountNumber(userName, userEmail, userPassword);

            //Checking to see if account was found. If so, re-prompting user for credentials
            if (accountNumber > 0)
            {
                cout << duplicateAccountError << endl;
            }
            else if (accountNumber == 0)
            {
                cout << duplicateEmailError << endl;
            }
            else
            {
                foundAccount = false;
                system("CLS");
                cout << accountCreationSuccess << flush;
            }
        }
        
    }


    //Creating new User object
    User* newUser = new User(userName, userEmail, userPassword);


    //Setting account number or create new account
    if (accountChoice == 1)
    {
        newUser->SetAccount(accountNumber);
    }
    else
    {
        newUser->createAccount();
    }



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

            for (FridgeItem* i : contents)
            {
                ItemInfo* item = i->itemInfo;
                cout << item->displayName << "| " << item->fullName << "| " << item->sku << "| ";
                cout << i->dateDay << ", " << i->dateYear << "| " << i->quantity << "| " << i->goodFor;
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
        case 7: //Quit the SmileFridge app
            cout << "\nThanks for using the SmileFridge app! Goodbye.";
        }
    }

    //Deleting user dynamic memory
    delete newUser;



    return 0;
} //End Main






//*****************************************************************************************
//***findAccountNumber method***														***
//***This method attempts to find a user account by searching each line of the accounts ***
//***csv file for the user entered credentials. If the credentials match a line in the  ***
//***csv file, then the account number is returned. If the email entered matches an     ***
//***email in one of the rows but not everything else matches, a 0 is returned. Fianlly,***
//***if no account is matched by the user entered credentials, a -1 is returned.
//*****************************************************************************************
long int findAccountNumber(string userName, string userEmail, string userPassword)
{
    //Opening accounts file that contains all user information
    ifstream existingAccountFile("accounts.csv");

    if (!existingAccountFile.is_open())	// Check if file exists
    {
        //if accounts.csv file doesn't exist, then user account can't exist
        return -1;
    }
    else
    {
        //Creating variables for searching file
        string nextAccountLine;
        long int accountNumber;
        string newUserName;
        string newUserEmail;
        string newUserPassword;
        string nextString;
        vector<string> row;

        //Searching account.csv file for a matching account
        while (!existingAccountFile.eof())
        {
            row.clear();

            //Getting each line of csv and adding separated values to vector
            getline(existingAccountFile, nextAccountLine);
            istringstream ss(nextAccountLine);

            while (getline(ss, nextString, ','))
            {
                row.push_back(nextString);
            }

            //Storing account information to variables
            accountNumber = stoi(row[0]);
            newUserEmail = row[1];
            newUserName = row[2];
            newUserPassword = row[3];

            //Account was found
            if (newUserName == userName && newUserEmail == userEmail && newUserPassword == userPassword)
            {
                return accountNumber;
            }
            else if (newUserEmail == userEmail) //If email has been used before but entire account doesn't match
            {
                return 0;
            }
        }

        //Account was not found
        return -1;
    }
        
}