#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;

struct InventoryItem
{
    string sku;
    int quantity;
    int dateYear;
    int dateDay;
    int goodFor;
    
    InventoryItem(string sku, int quantity, int dateYear, int dateDay, int goodFor) :
        sku(sku), quantity(quantity), dateYear(dateYear), dateDay(dateDay), goodFor(goodFor) { }

    void SetQuantity(int q) { quantity = q; }
    void LowerQuantity(int q = 1) { quantity -= q; }
};

class Inventory
{
private:
    vector<InventoryItem> _contents;
    void getInventoryFromCsv(string filename);
public:
    Inventory()
    {
        getInventoryFromCsv("inventory_list.csv");
    }
    vector<InventoryItem> GetContents() { return _contents; }
    void Use(string sku, int amount = 1);
    InventoryItem GetBySku(string sku);
};