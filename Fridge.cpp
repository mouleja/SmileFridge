#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>


#include "Fridge.hpp"

void Fridge::GetItemsFromCsv(string filename)
{
	// Note: partially adapted from https://stackoverflow.com/questions/19936483/c-reading-csv-file

	std::ifstream inFile(filename);

	if (inFile.bad())	// Check for error opening file
	{
		std::cout << "Error reading file: " << filename << std::endl;
		return;
	}

	string line, displayname, fullname, sku, date, quantStr, opStr, favStr;
	int quant, op;
	bool fav;

	while (getline(inFile, line))	// Get line from file
	{
		std::istringstream ss(line);	// Split into fields

		getline(ss, displayname, ',');
		getline(ss, fullname, ',');
		getline(ss, sku, ',');
		getline(ss, date, ',');
		getline(ss, quantStr, ',');
		getline(ss, opStr, ',');
		getline(ss, favStr, ',');

		quant = std::stoi(quantStr);
		op = std::stoi(opStr);

		if (favStr == "true")
		{
			fav = true;
		}
		else
		{
			fav = false;
		}

		_contents.insert({new Item(displayname, fullname, sku, date, op, fav), quant });	// Create {item, int} pair & add to map
	}

	inFile.close();
}

map<Item*, int> Fridge::GetFavorites() {
	map<Item*, int> favorites;
	for (map<Item*, int>::iterator it = _contents.begin(); it != _contents.end(); it++ ) {
		if (it->first->IsFavorite()) {
			favorites.insert({ it->first, it->second });
		}
	}
	return favorites;
}

/* Item Properties
	string _displayName;
	string _fullName;
	string _sku;
	string _date;
	int _quantity;
	int _orderPoint;
	bool _favorite;

*/