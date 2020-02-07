#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>


#include "Inventory.hpp"

void Inventory::getInventoryFromCsv(string filename)
{
	// Note: partially adapted from https://stackoverflow.com/questions/19936483/c-reading-csv-file

	std::ifstream inFile(filename);

	if (inFile.bad())	// Check for error opening file
	{
		std::cout <<"Error reading file: " << filename << std::endl;
		return;
	}

	string line, sku, dateYearStr, dateDayStr, quantStr, goodForStr;
	int dy, dd, quant, gf;
	bool fav;

	while (getline(inFile, line))	// Get line from file
	{
		std::istringstream ss(line);	// Split into fields

		getline(ss, sku, ',');
		getline(ss, dateYearStr, ',');
		getline(ss, dateDayStr, ',');
		getline(ss, quantStr, ',');
		getline(ss, goodForStr, ',');

		dy = std::stoi(dateYearStr);
		dd = std::stoi(dateDayStr);
		quant = std::stoi(quantStr);
		gf = std::stoi(goodForStr);

		_contents.push_back(InventoryItem(sku, dy, dd, quant, gf));	// Create object & add to vector
	}

	inFile.close();
}


InventoryItem Inventory::GetBySku(string sku)
{
	for (InventoryItem i : _contents)
	{
		if (i.sku == sku) return i;
	}
}