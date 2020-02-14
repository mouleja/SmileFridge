#include "OrderList.hpp";

void OrderList::add(ItemInfo* item) {
	list.push_back(item);
}

void OrderList::remove(ItemInfo* item) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == item) {
			list.erase(list.begin()+i);
			return;
		}
	}
}

void OrderList::clearAll() {
	list.clear();
}
