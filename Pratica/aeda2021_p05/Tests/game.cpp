#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO
Game::Game()
{
}

// TODO
Game::Game(list<Kid>& l2)
{
  kids=l2;
}

// TODO
void Game::addKid(const Kid &k1)
{
  kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const
{
    return kids;
}

// TODO
string Game::write() const
{
  string inGame;
  for (const auto & kid : kids){
    inGame += kid.write() + "\n";
  }
  return inGame;
}

// TODO
Kid& Game::loseGame(string phrase)
{
  int n = numberOfWords(phrase)-1;
  auto it = kids.begin();

  while (kids.size() != 1) {
    it = kids.begin();
    for (int i = 0; i < (n%kids.size()); i++) {
      it++;
    }

    kids.erase(it);
  }
  return kids.front();
}

// TODO
list<Kid>& Game::reverse()
{
  kids.reverse();
  return kids;
}

// TODO
list<Kid> Game::removeOlder(unsigned id)
{
  kids.remove_if([id](const Kid& kid){return kid.getAge()<=id;});
  return kids;
}

// TODO
void Game::setKids(const list<Kid>& l1)
{
  kids.insert(kids.end(), l1.begin(), l1.end());
}

// TODO
bool Game::operator==(Game& g2)
{
  if (kids.size() == g2.kids.size()){
    auto it1 = kids.begin();
    auto it2 = g2.kids.begin();
    while (it1 != kids.end()){
      if (! ((*it1)==(*it2))){
        return false;
      }
      it1++;
      it2++;
    }
    return true;
  }
  else
    return false;
}

// TODO
list<Kid> Game::shuffle() const
{
  srand(time(nullptr));
  list<Kid> shuffleKids;
  auto its = shuffleKids.begin();
  for (auto it = kids.begin(); it != kids.end();it++){
    its = shuffleKids.begin();
    for (size_t i = 0; i < rand()%kids.size(); i++){
      its++;
    }
    shuffleKids.insert(its, (*it));
  }
  return shuffleKids;

}
