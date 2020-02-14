#pragma once

#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>

#define ITEMSFILE "items_list.csv"

struct ItemInfo {
    string displayName;
    string fullName;
    string sku;
    int minQuantity;
	int orderQuantity;
    bool favorite;
	ItemInfo(string displayname, string fullname, string sku, int minQuantity, int ordQuantity, bool favorite)
		: displayName(displayname), fullName(fullname), sku(sku), minQuantity(minQuantity), orderQuantity(ordQuantity), favorite(favorite) { }
    ItemInfo(string displayname, string fullname, string sku)
        : displayName(displayname), fullName(fullname), sku(sku), minQuantity(0), orderQuantity(1), favorite(false) { }
};

class Items
{
private:
    map<string, ItemInfo*> _items;
    void getItemsFromCsv(string filename);

public:
    Items();
    map<string, ItemInfo*> GetAll() { return _items; }
    ItemInfo* GetBySku(string sku) { return _items[sku]; }
    bool isFavorite(string sku);
    std::vector<string> GetFavoriteSkus();
    void SetMinQuantity(string sku, int amount);
    void SetFavorite(string sku, bool fav = true);
};

