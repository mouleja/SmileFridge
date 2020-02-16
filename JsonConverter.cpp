#include "JsonConverter.hpp"

string GetFridgeJson(vector<FridgeItem*> items, string listName)
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

string PrettyPrintJson(string json)
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

void ppj_newline(string &result, int tabs)
{
    result += '\n';
    for (int j = 0; j < tabs; ++j)
    {
        result += "\t";
    }
}