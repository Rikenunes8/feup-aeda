/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"


BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string name) {
    setName(name);
    id=next_id++;
}

bool BankOfficer::operator>(const BankOfficer &officer) const {
    if (myAccounts.size() == officer.myAccounts.size())
        return name > officer.getName();
    else
        return myAccounts.size() > officer.myAccounts.size();
}

bool BankOfficer::operator==(const BankOfficer &officer) const {
    return name==officer.getName();
}


