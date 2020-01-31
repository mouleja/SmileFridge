#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Inventory.hpp"

void Inventory::GetItemsFromCsv(string filename)
{
	// Note: partially adapted from https://stackoverflow.com/questions/19936483/c-reading-csv-file

	std::ifstream inFile(filename);

	if (inFile.bad())	// Check for error opening file
	{
		std::cout <<"Error reading file: " << filename << std::endl;
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

		_contents.push_back(new Item(displayname, fullname, sku, date, quant, op, fav));	// Create object & add to vector
	}

	inFile.close();
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