#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

#include "Items.hpp"

class Inventory
{
private:
    vector<Items*> _contents;
    void GetItemsFromCsv(string filename);
public:
    Inventory()
    {
        _contents = vector<Items*>();
        GetItemsFromCsv("itemslist.csv");
    }
    vector<Items*> GetContents() { return _contents; }
	vector<Items*> GetFavorites();
  void AddItem(string, int);
  void RemoveItem(string, int);
  void CreateNewItem(string, string, string);
  int ItemInContents(string);
};
