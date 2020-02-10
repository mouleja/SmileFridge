#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

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
	vector<Item*> GetFavorites();
  void AddItem(string, int);
  void RemoveItem(string, int);
  void CreateNewItem(string, string, string);
  int ItemInContents(string);
};
