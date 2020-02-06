#pragma once

#include <string>
using std::string;

#include <ctime>

class Item
{
private:
    string _displayName;
    string _fullName;
    string _sku;
    string _date;
    int _orderPoint;
    bool _favorite;

public:
    Item(
        string displayName,
        string fullName,
        string sku,
        string date,
        int orderPoint,
        bool favorite
    ) :
        _displayName(displayName),
        _fullName(fullName),
        _sku(sku),
        _date(date),
        _orderPoint(orderPoint),
        _favorite(favorite)
    { }

    string GetDisplayName() const { return _displayName; }
    string GetFullName() const { return _fullName; }
    string GetSku() const { return _sku; }
    string GetDate() const { return _date; }
    int GetOrderPoint() const { return _orderPoint; }
    bool IsFavorite() const { return _favorite; }

    void SetDate(string newDate) { _date = newDate; }
    void SetOrdePoint(int op) { _orderPoint = op; }
    void MakeFavorite() { _favorite = true; }
    void RemoveFavorite() { _favorite = false; }
};

