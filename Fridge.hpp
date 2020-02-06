#pragma once

#include <map>
using std::map;
using std::string;

#include "Item.hpp"
#include "User.hpp"

class Fridge
{
private:
	User* _user;
	map<Item*, int> _contents;
	void GetItemsFromCsv(string filename);
public:
	Fridge(User* user) : _user(user)
	{
		_contents = map<Item*, int>();
		GetItemsFromCsv("itemslist.csv");
	} 
	map<Item*, int> GetContents() { return _contents; }
	map<Item*, int> GetFavorites();

};