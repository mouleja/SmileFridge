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
    bool favorite;
	ItemInfo(string displayname, string fullname, string sku, int minQuantity, bool favorite)
		: displayName(displayname), fullName(fullname), sku(sku), minQuantity(minQuantity), favorite(favorite) { }
    ItemInfo(string displayname, string fullname, string sku)
        : displayName(displayname), fullName(fullname), sku(sku), minQuantity(0), favorite(false) { }
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

