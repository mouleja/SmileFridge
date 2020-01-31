#pragma once

#include <vector>
using std::vector;

#include "Item.hpp"

class Inventory
{
private:
    vector<Item*> _contents;
    void GetItemsFromCsv(string filename);
public:
    Inventory()
    {
        _contents = vector<Item*>();
        GetItemsFromCsv("itemslist.csv");
    }
    vector<Item*> GetContents() { return _contents; }

};