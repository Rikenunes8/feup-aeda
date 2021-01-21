#include "game.h"
#include <sstream>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
    if (c1.getState())
        os << c1.getPoints() << "-" << "true-" << c1.getNVisits() << endl;
    else
        os << c1.getPoints() << "-" << "false-" << c1.getNVisits() << endl;
    return os;
}

BinaryTree<Circle> Game::Helper(int pos, int h, vector<int> &points, vector<bool> &states) {
    Circle c(points[pos], states[pos]);
    if (h == 0) return BinaryTree<Circle>(c);
    BinaryTree<Circle> left = Helper(2*pos+1, h-1, points, states);
    BinaryTree<Circle> right = Helper(2*pos+2, h-1, points, states);
    return BinaryTree<Circle>(c, left, right);
}
//TODO
Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    game = Helper(0, h, points, states);
}


//TODO
string Game::writeGame()
{
    stringstream ss;
    BTItrLevel<Circle> it(game);
    while (!it.isAtEnd()) {
        ss << it.retrieve();
        it.advance();
    }
    return ss.str();
}


//TODO
int Game::move()
{
    BTItrLevel<Circle> it(game);
    int i = 0;
    int target = 0;
    int final;
    while (!it.isAtEnd()) {
        if (i == target) {
            if (it.retrieve().getState())
                target = 2*target + 2;
            else
                target = 2*target +1;
            it.retrieve().changeState();
            it.retrieve().increaseVisits();
            final = it.retrieve().getPoints();
        }
        i++;
        it.advance();
    }
    return final;
}


//TODO
int Game::mostVisited()
{
    BTItrLevel<Circle> it(game);
    it.advance();
    int mostVisited = 0;
    while (!it.isAtEnd()) {
        if (it.retrieve().getNVisits() > mostVisited)
            mostVisited = it.retrieve().getNVisits();
        it.advance();
    }
    return mostVisited;
}
