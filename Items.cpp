#include "Items.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>

Items::Items()
{
	getItemsFromCsv(ITEMSFILE);
}

bool Items::isFavorite(string sku)
{
	return (_items[sku]->favorite == true);
}

// Change minQuanity for an item (by sku)
void Items::SetMinQuantity(string sku, int amount)
{
	if (_items.find(sku) != _items.end())
	{
		_items[sku]->minQuantity = amount;
	}
}

// Set favorite status(bool, default = true) of item by sku.
void Items::SetFavorite(string sku, bool fav)
{
	if (_items.find(sku) != _items.end())
	{
		_items[sku]->favorite = fav;
	}
}

void Items::getItemsFromCsv(string filename)
{
	// Note: partially adapted from https://stackoverflow.com/questions/19936483/c-reading-csv-file

	std::ifstream inFile(filename);

	if (inFile.bad())	// Check for error opening file
	{
		std::cout << "Error reading file: " << filename << std::endl;
		return;
	}

	string line, displayname, fullname, sku, quantStr, mqStr, oqStr, favStr;
	int mq, oq;
	bool fav;

	while (getline(inFile, line))	// Get line from file
	{
		std::istringstream ss(line);	// Split into fields

		getline(ss, displayname, ',');
		getline(ss, fullname, ',');
		getline(ss, sku, ',');
		getline(ss, mqStr, ',');
		getline(ss, oqStr, ',');
		getline(ss, favStr, ',');

		mq = std::stoi(mqStr);
		oq = std::stoi(oqStr);

		if (favStr == "true")
		{
			fav = true;
		}
		else
		{
			fav = false;
		}

		ItemInfo* current = new ItemInfo(sku, displayname, fullname, mq, oq, fav);
		_items.insert({ sku, current });	// Create {sku, itemInfo*} pair & add to map
	}

	inFile.close();
}

