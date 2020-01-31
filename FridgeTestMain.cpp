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
//#include "Item.hpp"

int main()
{
    cout << endl << "Welcome to your SmileFridge!!!" << endl << endl;

    User *user = new User("Joe Blow", "joe@blow.com", "AFE87WE34FES");

    return 0;
}

