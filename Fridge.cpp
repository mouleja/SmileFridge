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

	for (std::map<string, ItemInfo*>::iterator it = _items.begin(); it != _items.end(); it++) {
		
		//only add the item to the order list if it has a designated minimum quantity threshold
		if (it->second->minQuantity > 0) {

			int index = GetIndexBySku(it->first);

			//if the fridge is not currently stocked with the item
			if (index == -1) {
				int orderMultiple = 1;
				//ensure amount to be ordered is greater than the designated minimum quantity for the item
				while (orderMultiple * it->second->orderQuantity < it->second->minQuantity) orderMultiple++;
				//add item to order list
				orderList.insert({ it->first, orderMultiple });
				/* No need to worry about adding too many items to the orderList if orderLowItems() is called multiple times
				   before an order is received since the orderList is a map and the appropriate quantity will be overwritten
				   at the corresponding sku key rather than indexed multiple times as a {key, value} element in the map */
			}//end if

			//if the fridge has a current quantity for the item and it's below minQuantity
			else if (_contents[index]->quantity < it->second->minQuantity) {
				int orderMultiple = 1;
				int currentQuantity = _contents[index]->quantity + it->second->orderQuantity;
				while (currentQuantity < it->second->minQuantity) {
					currentQuantity += it->second->orderQuantity;
					orderMultiple++;
				}//end while
				//add item and quantity to order list
				orderList.insert({ it->first, orderMultiple });
			}//end else if

		}//end outer if

	}//end for loop
}//end orderLowItems

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
		int index = GetIndexBySku(it->first);
		if (index == -1) {
			/*Hardcoded fridge data temporarily: in actual application get it from Date Time function when order is received*/
			FridgeItem *newItem = new FridgeItem(_items.at(it->first), (it->second * _items.at(it->first)->orderQuantity), 2020, 46, 30);
			_contents.push_back(newItem);
		}
		else {
			FridgeItem* updateItem = _contents[GetIndexBySku(it->first)];
			updateItem->quantity += (it->second * updateItem->itemInfo->orderQuantity);
		}
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