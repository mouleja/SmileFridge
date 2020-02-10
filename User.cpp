/******************************************************************************
** Program name: SmileFridge.cpp
** Authors: Ryan Jones
** CS361-400-W20
** Date: 02/09/20
** Description: User class file for creating new users, logging in existing
**				users, finding/creating the correct csv file for that user
**				and returning user information if needed.
******************************************************************************/

#include "User.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::istringstream;
using std::to_string;

void User::findAccountNumber()
{

}

//*****************************************************************************************
//***createAccount method***															***
//***This method creates a new user account by either creating the accounts file		***
//***that stores all user account information or opening the existing accounts file and ***
//***adding the new user's information. It also creates a new csv file named after the  ***
//***newly created account number for storing inventory information in later.			***
//*****************************************************************************************
void User::createAccount()
{
	//Opening accounts file that contains all user information
	ifstream existingAccountFile("accounts.csv");

	if (!existingAccountFile.is_open())	// Check if file exists
	{
		//accounts.csv file doesn't exist, create it by 'opening it'
		fstream accountFile;
		accountFile.open("accounts.csv", std::fstream::out);

		//Set first account number
		SetAccount(1000000);
		accountFile << GetAccount() << "," << GetEmail() << "," << GetName() << "," << GetPassword();

		//Close accounts file
		accountFile.close();

	}
	else
	{
		//Extracting last line of accounts file
		string accountFileLastLine;
		int lastAccountNumber;
		while (!existingAccountFile.eof())
		{
			getline(existingAccountFile, accountFileLastLine);
		}

		//Extracting last created account number
		istringstream ss(accountFileLastLine);
		ss >> lastAccountNumber;
		
		//Open accounts.csv for appending new user information
		fstream accountFile;
		accountFile.open("accounts.csv", std::fstream::app);

		//Set new account number
		SetAccount(lastAccountNumber + 1);
		accountFile << "\n" << GetAccount() << "," << GetEmail() << "," << GetName() << "," << GetPassword();
		accountFile.close();
	}

	//Creating account specific file for inventory tracking
	ofstream accountSpecificFile;
	accountSpecificFile.open(to_string(GetAccount()) + ".csv");
	accountSpecificFile.close();

	//Close existing accounts file
	existingAccountFile.close();

}