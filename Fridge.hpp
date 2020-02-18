#pragma once

#include <vector>
using std::vector;

#include "Items.hpp"
#include "User.hpp"
#include "DateConverter.hpp"

#define INVFILE "inventory_list.csv"
#define ORDERLOG "order_log.csv"

struct FridgeItem
{
	ItemInfo *itemInfo;
	int quantity;
	Date dateStocked;
	int goodFor;

	FridgeItem(ItemInfo *itemInfo, int quantity, Date dateStocked, int goodFor) :
		itemInfo(itemInfo), quantity(quantity), dateStocked(dateStocked), goodFor(goodFor) 
	{ }
};

class Supplier;	// Forward declaration

class Fridge
{
private:
	User* _user;
	Supplier* _supplier;
	map<string, ItemInfo*> _items;
	vector<FridgeItem*> _contents;
	map<string, int> groceryList;
	map<string, int> orderList;
	int _nextOrderNumber;
	void getInventoryFromCsv(string sku);
	int getNextOrderNumber();

public:
	Fridge(User* user);

	User* GetUser() { return _user; }
	vector<FridgeItem*> GetContents() { return _contents; }
	map<string, ItemInfo*> GetAllItems() { return _items; }
	bool isFavorite(string sku) { return _items.at(sku)->favorite; }
	void Use(string sku, int amount = 1);
	int GetIndexBySku(string sku);
	FridgeItem* GetInfoBySku(string sku);
	vector<ItemInfo*> GetFavorites();
	void AddItem(string sku, int quantity);
	void orderLowItems();
	void updateInventory();
	void placeOrder();
	void printOrderList();
	void SubmitOrder();
};