#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


//TODO
bool Bet::contains(unsigned num) const
{
    tabHInt::const_iterator it = numbers.find(num);
    return it != numbers.end();
}

//TODO
void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    numbers.clear();
    pair<tabHInt::iterator, bool> p;
    int i = 0, index = 0;
    while (i < n) {
        p = numbers.insert(values[index]);
        if (p.second)
            i++;
        index++;
    }
}

//TODO
unsigned Bet::countRights(const tabHInt& draw) const
{
    int i = 0;
	for (tabHInt::const_iterator it = draw.begin(); it != draw.end(); it++) {
	    if (contains(*it))
	        i++;
	}
    return i;
}

bool Bet::operator==(const Bet &b) const {
    for (auto n:numbers) {
        if (!b.contains(n))
            return false;
    }

    for (auto n:b.getNumbers()) {
        if (!contains(n))
            return false;
    }
    return true;
}

bool Bet::winBet(const tabHInt& draw) const {
    int match = 0;
    for (tabHInt::const_iterator it = draw.cbegin(); it != draw.cend(); it++) {
        if (contains(*it))
            match++;
    }
    return match > 3;
}
