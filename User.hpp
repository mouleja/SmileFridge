#pragma once

#include <string>
using std::string;

class User
{
private:
	string _name;		// Name of the user
	string _email;		// User email
	long int _account;	// Amazon account number?
	string _password;	// SmileFridge password (Amazon password?)
public:
	User(string name, string email, string password) : _name(name), _email(email), _account(-1000000), _password(password) { }
	string GetName() const { return _name; }
	string GetEmail() const { return _email; }
	long int GetAccount() const { return _account; }
	string GetPassword() const { return _password; } //A bad idea in practice, could implement a hash table later to encrypt?
	void SetAccount(int newAccountNumber) { _account = newAccountNumber; }
	void findAccountNumber();
	void createAccount();
};