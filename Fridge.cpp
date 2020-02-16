#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Fridge.hpp"

// 	FridgeItem(string displayName, string fullName, string sku, int minQuantity,
//  bool favorite, int quantity, int dateYear, int dateDay, int goodFor) :

void Fridge::getInventoryFromCsv(string filename)
{
	// Note: partially adapted from https://stackoverflow.com/questions/19936483/c-reading-csv-file

	std::ifstream inFile(filename);

	if (inFile.bad())	// Check for error opening file
	{
		std::cout << "FATAL Error reading file: " << filename << std::endl;
		exit(1);
	}

	string line, sku, dateYearStr, dateDayStr, quantStr, goodForStr;
	int dy, dd, quant, gf;

	while (getline(inFile, line))	// Get line from file
	{
		std::istringstream ss(line);	// Split into fields

		getline(ss, sku, ',');
		getline(ss, quantStr, ',');
		getline(ss, dateYearStr, ',');
		getline(ss, dateDayStr, ',');
		getline(ss, goodForStr, ',');

		dy = std::stoi(dateYearStr);
		dd = std::stoi(dateDayStr);
		quant = std::stoi(quantStr);
		gf = std::stoi(goodForStr);

		ItemInfo *item = _items.at(sku);	// This will throw an error if sku not in _items!!
		Date ds(dy, dd);

		_contents.push_back(new FridgeItem(item, quant, ds, gf));
	}

	inFile.close();
}

// Remove some amount(default = 1) from item by sku.  Removes item from contents if quantity < 0.
void Fridge::Use(string sku, int amount)
{
	FridgeItem* item = GetInfoBySku(sku);
	if (item)
	{
		item->quantity -= amount;
		if (item->quantity < 1)
		{
			int index = GetIndexBySku(sku);
			_contents.erase(_contents.begin() + index);
		}
	}
}

int Fridge::GetIndexBySku(string sku)
{
	for (unsigned i = 0; i < _contents.size(); ++i)
	{
		if (_contents[i]->itemInfo->sku == sku)
		{
			return i;
		}
	}
	return -1;
}

FridgeItem* Fridge::GetInfoBySku(string sku)
{
	for (unsigned i = 0; i < _contents.size(); ++i)
	{
		if (_contents[i]->itemInfo->sku == sku)
		{
			return _contents[i];
		}
	}
	return nullptr;
}

// returns all favorites regardless of current stock
vector<ItemInfo*> Fridge::GetFavorites()
{
	vector<ItemInfo*> favorites;
	map<string, ItemInfo*>::iterator it = _items.begin();
	while (it != _items.end())
	{
		ItemInfo* item = it->second;
		if (item->favorite)
		{
			favorites.push_back(item);
		}
		++it;
	}
	return favorites;
}

//Adds an item to the list of contents. Runs the "CreateNewItem" function
//if the item is not in contents already. Needs to be adjusted to track
//items that are already known but not in contents
void Fridge::AddItem(string sku, int quantity) {
	//Will return -1 if item was not found
	int place = this->GetIndexBySku(sku);
	if (place < 0) {
		ItemInfo* new_item = new ItemInfo(sku);
		this->_contents.push_back(new FridgeItem(new_item, quantity, Date(1, 1), 9999));
	}
	else
	{
		this->_contents[place]->quantity += quantity;
	}
}