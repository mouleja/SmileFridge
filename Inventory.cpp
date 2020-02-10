#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time>


#include "Inventory.hpp"

void Inventory::GetItemsFromCsv(string filename)
{
	// Note: partially adapted from https://stackoverflow.com/questions/19936483/c-reading-csv-file

	std::ifstream inFile(filename);

	if (inFile.bad())	// Check for error opening file
	{
		std::cout <<"Error reading file: " << filename << std::endl;
		return;
	}

	string line, displayname, fullname, sku, date, quantStr, opStr, favStr;
	int quant, op;
	bool fav;

	while (getline(inFile, line))	// Get line from file
	{
		std::istringstream ss(line);	// Split into fields

		getline(ss, displayname, ',');
		getline(ss, fullname, ',');
		getline(ss, sku, ',');
		getline(ss, date, ',');
		getline(ss, quantStr, ',');
		getline(ss, opStr, ',');
		getline(ss, favStr, ',');

		quant = std::stoi(quantStr);
		op = std::stoi(opStr);

		if (favStr == "true")
		{
			fav = true;
		}
		else
		{
			fav = false;
		}

		_contents.push_back(new Item(displayname, fullname, sku, date, quant, op, fav));	// Create object & add to vector
	}

	inFile.close();
}

vector<Item*> Inventory::GetFavorites() {
	vector<Item*> favorites;
	for (Item* item : _contents) {
		if (item->IsFavorite()) {
			favorites.push_back(item);
		}
	}
	return favorites;

//Adds an item to the list of contents. Runs the "CreateNewItem" function
//if the item is not in contents already. Needs to be adjusted to track
//items that are already known but not in contents
void Inventory::AddItem(string name, int quantity){
	//Will return -1 if item was not found
	int place = this->ItemInContents(name);
	if(place < 0){
		Item* new_item = this->CreateNewItem(name, name, "Unknown");
		this->_contents.push_back(new_item);
		place = this->_contents.size() - 1;
	}
	this->_contents[i]->AddQuantity(quantity);
}

//If the item exists in the fridge's contents, remove the given number
//of units from the fridge. If that brings it below 0, then set the quantity
//to 0.
void Inventory::RemoveItem(string name, int quantity){
	int place = this->ItemInContents(name);
	if(!(place < 0 || place > this->_contents.size())){
		this->_contents[place]->RemoveQuantity(quantity);
		if(this->_contents[place]->GetQuantity() < 0){
			this->_contents[place]->SetQuantity(0);
		}
	}
}

//Creates a new item with the given display name, full name, and SKU with the current date.
Item* Inventory::CreateNewItem(string display_name, string full_name, string sku){
	tm *ltm = localtime(&now);
	string date = static_cast<string>(ltm->tm_month) + "/" + static_cast<string>(ltm->tm_day) + "/" + static_cast<string>(1900 + ltm->tm_year);
	Item* new_item = new Item(display_name, full_name, sku, date, 0, 0, false);
	return new_item;
}

int Inventory::ItemInContents(string name){
	//Checks the name we're looking for agains the full name and display name
	//of each item in the fridge's contents and returns the index of the item, or
	//-1 if it doesn't exist.
	for(int i = 0; i < this->_contents.size(); i++){
		if(strcmp(name, this->_contents[i]->displayName) == 0 ||
		 	 strcmp(name, this->_contents[i]->fullName == 0){
				 return i;
		}
	}
	return -1;
}


/* Item Properties
	string _displayName;
	string _fullName;
	string _sku;
	string _date;
	int _quantity;
	int _orderPoint;
	bool _favorite;

*/
