#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;

#include "Fridge.hpp"

string GetFridgeJson(vector<FridgeItem*> items, string listName);
string PrettyPrintJson(string json);
void ppj_newline(string& result, int tabs);
string GetOrderListJson(map<string, int> list);
