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

		_contents.push_back(
			new FridgeItem(item, quant, dy, dd, gf)
		);
	}

	inFile.close();
}

// Remove some amount(default = 1) from item by sku.  Removes item from contents if quantity < 0.
void Fridge::Use(string sku, int amount)
{
	int index = GetIndexBySku(sku);
	if (index > -1)
	{
		_contents[index]->quantity -= amount;
		if (_contents[index]->quantity < 1)
		{
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

void Fridge::orderLowItems() {
	for (int i = 0; i < _contents.size(); i++) {
		if (_contents[i]->quantity < _contents[i]->itemInfo->minQuantity) {
			int orderMultiple = 1;
			int currentQuant = _contents[i]->quantity;
			int minQuant = _contents[i]->itemInfo->minQuantity;
			while (currentQuant < minQuant) {
				currentQuant += _contents[i]->itemInfo->orderQuantity;
				orderMultiple++;
			}//end while
			orderList.insert({ _contents[i]->itemInfo->sku, orderMultiple });
		}//end if
	}//end for
}

void Fridge::updateInventory() {
	std::ofstream outFile(INVFILE, std::ios::trunc);
	for (FridgeItem* fridgeItem : _contents) {
		ItemInfo* item = fridgeItem->itemInfo;
		outFile << item->sku << "," << fridgeItem->quantity << "," << fridgeItem->dateYear << "," << fridgeItem->dateDay
			<< "," << fridgeItem->goodFor << std::endl;
	}
	outFile.close();
}

void Fridge::placeOrder() {
	for (std::map<string, int>::iterator it = orderList.begin(); it != orderList.end(); it++) {
		FridgeItem* updateItem = _contents[GetIndexBySku(it->first)];
		updateItem->quantity += (it->second * updateItem->itemInfo->orderQuantity);
	}
	orderList.clear();
}

void Fridge::printOrderList() {
	std::cout << "Item name | Order Units" << std::endl << std::endl;
	for (std::map<string, int>::iterator it = orderList.begin(); it != orderList.end(); it++) {
		ItemInfo* orderItem = _items.at(it->first);
		std::cout << orderItem->displayName << " | " << it->second << std::endl;
	}
}