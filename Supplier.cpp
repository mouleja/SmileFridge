#include "Supplier.hpp"
#include "Fridge.hpp"
#include <fstream>


string Supplier::GetFridgeJson(vector<FridgeItem*> items, string listName)
{
    string result = "{\"" + listName + "\": [";
    for (FridgeItem* i : items)
    {
        result += "{\"sku\": \"" + i->itemInfo->sku + "\", ";
        result += "\"name\": \"" + i->itemInfo->displayName + "\"}, ";
    }
    result.erase(result.end() - 2, result.end());   // erase last comma and space
    result += "]}\n";
    return result;
}

string Supplier::PrettyPrintJson(string json)
{
    string result = "";
    int tabs = 0;
    string insertStr;
    for (size_t i = 0; i < json.size(); ++i)
    {
        if (json[i] == '{' || json[i] == '[')
        {
            ++tabs;
            result += json[i];
            ppj_newline(result, tabs);
        }
        else if (json[i] == '}' || json[i] == ']')
        {
            --tabs;
            ppj_newline(result, tabs);
            result += json[i];
            if (json[i + 1] == ',')
            {
                result += ',';
                ++i;
            }
            ppj_newline(result, tabs);
        }
        else if (json[i] == ',')
        {
            result += ',';
            ppj_newline(result, tabs);
        }
        else
        {
            result += json[i];
        }
    }
    return result;
}

void Supplier::ppj_newline(string &result, int tabs)
{
    result += '\n';
    for (int j = 0; j < tabs; ++j)
    {
        result += "\t";
    }
}

void Supplier::addToOrderLog(string listJson)
{

}

string Supplier::GetOrderListJson(map<string, int> list)
{
    string result = "{\"order\": [";
    for (std::map<string, int>::iterator it = list.begin(); it != list.end(); it++) {
        result += "{\"" + it->first + "\": \"" + std::to_string(it->second) + "\"}, ";
    }
    result.erase(result.end() - 2, result.end());
    result += "]}";
    return result;
}

void Supplier::CreateOrder(User* user, map<string, int> orderList, int orderNumber)
{
    // NOTE: at some point an API token will need to replace sending clear text account info
    string orderJson = "{{\"account\": ";
    string userJson = "{\"Number\": \"" + std::to_string(user->GetAccount()) + "\", \"Email\": \"" +
        user->GetEmail() + "\", \"Password\": \"" + user->GetPassword() + "\"}";
    string listJson = GetOrderListJson(orderList);
    orderJson += userJson + ", " + listJson + "}";

    // TODO: network code to send orderJson to Amazon (There is no _public_ API for this.)

    // Add order to order log file
    std::ofstream logFile(ORDERLOG, std::ofstream::app);
    logFile << orderNumber << "," << GetDateString(GetCurrentDate()) << "," << listJson << std::endl;
    logFile.close();
}
