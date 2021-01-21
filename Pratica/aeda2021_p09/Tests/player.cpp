#include "player.h"

//TODO
void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

//TODO
unsigned Player::betsInNumber(unsigned num) const
{
    int i = 0;
    for (auto b:bets) {
        if (b.contains(num))
            i++;
    }
    return i;
}

//TODO
tabHBet Player::drawnBets(const tabHInt& draw) const
{
    tabHBet res;
    for (auto b:bets) {
        if (b.winBet(draw))
            res.insert(b);
    }
	return res;
}
