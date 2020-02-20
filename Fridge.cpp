#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Fridge.hpp"
#include "Supplier.hpp"


// 	FridgeItem(string displayName, string fullName, string sku, int minQuantity,
//  bool favorite, int quantity, int dateYear, int dateDay, int goodFor) :

Fridge::Fridge(User* user)
{
	_user = user;
	_supplier = new Supplier();

	_items = Items().GetAll();

	getInventoryFromCsv(INVFILE);
}

void Fridge::getInventoryFromCsv(string filename)
{
	// Note: partially adapted from https://stackoverflow.com/questions/19936483/c-reading-csv-file

	std::ifstream inFile(filename);

	if (inFile.bad())	// Check for error opening file
	{
		std::cout << "FATAL Error reading file: " << filename << std::endl;
		exit(1);
	}

	string line, sku, dateYearStr, dateDayStr, quantStr, qooStr;
	int dy, dd, quant, qoo;

	while (getline(inFile, line))	// Get line from file
	{
		std::istringstream ss(line);	// Split into fields

		getline(ss, sku, ',');
		getline(ss, quantStr, ',');
		getline(ss, qooStr, ',');
		getline(ss, dateYearStr, ',');
		getline(ss, dateDayStr, ',');

		dy = std::stoi(dateYearStr);
		dd = std::stoi(dateDayStr);
		quant = std::stoi(quantStr);
		qoo = std::stoi(qooStr);

		ItemInfo *item = _items.at(sku);	// This will throw an error if sku not in _items!!
		Date ds(dy, dd);

		_contents.push_back(new FridgeItem(item, quant, qoo, ds));
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
		if (item->quantity < 1 && item->quantOnOrder < 1)
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
void Fridge::AddItem(string sku, int quantity, int quantOnOrder) {
	//Will return -1 if item was not found
	int place = this->GetIndexBySku(sku);
	if (place < 0) {
		ItemInfo* new_item = GetItemInfoBySku(sku);
		if (new_item == nullptr)
		{
			new_item = Items().CreateNewItem(sku);
		}
		this->_contents.push_back(new FridgeItem(new_item, quantity, quantOnOrder, GetCurrentDate()));
	}
	else
	{
		this->_contents[place]->quantity += quantity;
	}
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
			else if ((_contents[index]->quantity+_contents[index]->quantOnOrder) < it->second->minQuantity) {
				int orderMultiple = 1;
				int currentQuantity = (_contents[index]->quantity + _contents[index]->quantOnOrder) + it->second->orderQuantity;
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
		outFile << item->sku << "," << fridgeItem->quantity << "," << fridgeItem->quantOnOrder << ',' 
				<< fridgeItem->dateStocked.Year << "," << fridgeItem->dateStocked.Days << std::endl;
	}
	outFile.close();
}

void Fridge::printOrderList() {
	if (orderList.size() == 0)
	{
		std::cout << "You are not low on any items at this time." << std::endl;
		return;
	}

	std::cout << "Item name | Order Units | Quantity Ordered" << std::endl << std::endl;
	for (std::map<string, int>::iterator it = orderList.begin(); it != orderList.end(); it++) {
		ItemInfo* orderItem = _items.at(it->first);
		std::cout << orderItem->displayName << " | " << it->second 
			<< " | " << (orderItem->orderQuantity * it->second) << std::endl;
	}
	string output = _supplier->PrettyPrintJson(_supplier->GetOrderListJson(orderList));
	std::cout << output << std::endl;
}

void Fridge::SubmitOrder()
{
	//don't submit an order if the orderList is empty
	if (orderList.empty()) return;

	_supplier->CreateOrder(_user, orderList);
	std::cout << std::endl << "Order placed!" << std::endl;
	//loops through order items and finds matching items in fridge contents to update their 'quantOnOrder' field
	//or if ordered item is not in fridge contents, it is added with a quantity of 0 and appropriate 'quantOnOrder' value
	for (std::map<string, int>::iterator it = orderList.begin(); it != orderList.end(); it++) {
		if (GetIndexBySku(it->first) != -1)
			GetInfoBySku(it->first)->quantOnOrder = it->second * GetItemInfoBySku(it->first)->orderQuantity;
		else
			AddItem(it->first, 0, it->second * GetItemInfoBySku(it->first)->orderQuantity);
	}
	updateInventory();
	std::cout << "Current fridge items 'On-Order Quantity' successfully updated" << std::endl << std::endl;
	orderList.clear();	// Order placed and added to log
}

void Fridge::ReceiveOrder(string orderJson)
{
	vector<FridgeItem*> receivedItems = _supplier->ProcessReceivedOrder(orderJson);
	for (FridgeItem* recvdItem : receivedItems) {
		FridgeItem* currFridgeItem = GetInfoBySku(recvdItem->itemInfo->sku);
		currFridgeItem->quantity += recvdItem->quantity;
		currFridgeItem->quantOnOrder -= recvdItem->quantity;
	}
	updateInventory();
}

ItemInfo* Fridge::GetItemInfoBySku(string sku)
{
	if (_items.find(sku) != _items.end())
	{
		return _items[sku];
	}
	else
	{
		return nullptr;
	}
}
