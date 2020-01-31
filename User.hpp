#pragma once

#include <string>
using std::string;

class User
{
private:
	string _name;		// Name of the user
	string _email;		// User email
	string _account;		// Amazon account number
public:
	User(string name, string email, string account) : _name(name), _email(email), _account(account) { }
	string GetName() const { return _name; }
	string GetEmail() const { return _email; }
	string GetAccount() const { return _account; }

	
};