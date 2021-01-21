/*
 * Bank.h
 */

#ifndef SRC_BANK_H_
#define SRC_BANK_H_

#include "Account.h"
#include <vector>
#include <algorithm>

#include "BankOfficer.h"


template <class T>
bool inVector(const vector<T> &v, const T &elem) {
    for (auto e:v)
        if (e==elem)
            return true;
    return false;
}

template <class T>
unsigned int numberDifferent(const vector<T> &v1) {
    vector<T> temp;
    if (v1.empty())
        return 0;
    for (auto e:v1)
        if (!inVector(temp, e))
            temp.push_back(e);
    return temp.size();
}

class NoBankOfficerException {
        private:
            string name;
        public:
            NoBankOfficerException(string name) {this->name = name;}
            string getName() const {return name;}
};

class Bank {
	vector<Account *> accounts;
	vector<BankOfficer> bankOfficers;
public:
	Bank();
	void addAccount(Account *a);
	void addBankOfficer(BankOfficer b);
	vector<BankOfficer> getBankOfficers() const;
	vector<Account *> getAccounts() const;

	//-------
	double getWithdraw(string cod1) const;
	vector<Account *> removeBankOfficer(string name);
	const BankOfficer& addAccountToBankOfficer(Account *ac, string name);
	void sortAccounts();
};


#endif /* SRC_BANK_H_ */
