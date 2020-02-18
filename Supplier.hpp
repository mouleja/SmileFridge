#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <map>
using std::map;

#include "User.hpp"
#include "DateConverter.hpp"
struct FridgeItem;  // forward declaration

class Supplier
{
private:
    void ppj_newline(string& result, int tabs);
    void addToOrderLog(string);
public:
    string GetFridgeJson(vector<FridgeItem*> items, string listName);
    string PrettyPrintJson(string json);
    string GetOrderListJson(map<string, int> list);
    void CreateOrder(User* user, map<string, int> orderList, int orderNumber);
};


