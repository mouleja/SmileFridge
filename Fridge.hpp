#pragma once

#include <vector>
using std::vector;

#include "Items.hpp"
#include "User.hpp"

#define USERNAME "Joseph Blow"
#define EMAIL "joeb@low.com"
#define ACCTNO "AFE87WE34FES"
#define INVFILE "inventory_list.csv"

struct FridgeItem
{
	ItemInfo *itemInfo;
	int quantity;
	int dateYear;
	int dateDay;
	int goodFor;

	FridgeItem(ItemInfo *itemInfo, int quantity, int dateYear, int dateDay, int goodFor) :
		itemInfo(itemInfo), quantity(quantity), dateYear(dateYear), dateDay(dateDay), goodFor(goodFor) 
	{ }
};

class Fridge
{
private:
	User* _user;
	map<string, ItemInfo*> _items;
	vector<FridgeItem*> _contents;
	void getInventoryFromCsv(string sku);

public:
	Fridge()
	{
		_user = new User(USERNAME, EMAIL, ACCTNO);
		_items = Items().GetAll();
		getInventoryFromCsv(INVFILE);
	} 

	User* GetUser() { return _user; }
	vector<FridgeItem*> GetContents() { return _contents; }
	map<string, ItemInfo*> GetAllItems() { return _items; }
	bool isFavorite(string sku) { return _items.at(sku)->favorite; }
	void Use(string sku, int amount = 1);
	int GetIndexBySku(string sku);
};