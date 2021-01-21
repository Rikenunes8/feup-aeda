/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
	double n = 0;
	for (auto account:accounts) {
	    if (account->getCodH() == cod1)
	        n += account->getWithdraw();
	}
    return n;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	auto it = find_if(bankOfficers.begin(), bankOfficers.end(), [name](const BankOfficer &officer)
	                {return officer.getName() == name;});
    vector<Account*> v;
	if (it != bankOfficers.end()) {
        v = (*it).getAccounts();
        bankOfficers.erase(it);
	}
	return v;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    auto it = find_if(bankOfficers.begin(), bankOfficers.end(), [name](const BankOfficer &officer)
                {return officer.getName() == name;});
    if (it == bankOfficers.end())
        throw NoBankOfficerException(name);
    else
        (*it).addAccount(ac);
    return *it;
}

bool cmp(Account* a1, Account* a2) {
    if (a1->getBalance() == a2->getBalance())
        return (a1->getCodIBAN() < a2->getCodIBAN());
    else
        return (a1->getBalance() < a2->getBalance());
}
// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), cmp);
}

