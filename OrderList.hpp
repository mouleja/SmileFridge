#pragma once

#include "Items.hpp"

using std::vector;

class OrderList {

private:
	vector<ItemInfo*> list;
public:
	OrderList(){};
	void add(ItemInfo* item);
	void remove(ItemInfo* item);
	void clearAll();

};