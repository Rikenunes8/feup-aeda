#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;


bool InfoCard::operator==(const InfoCard& card) const{
  return name == card.name;
}

bool InfoCard::operator<(const InfoCard& card) const{
  if (frequency == card.frequency)
    return name < card.name;
  else
    return frequency > card.frequency;
}

bool InfoCard::cmpName(const InfoCard& card) const{
  return name < card.name;
}

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}

// TODO
int CarPark::clientPosition(const string & name) const
{
  InfoCard card;
  card.name = name;
  return sequentialSearch(clients, card);
}

// TODO
unsigned CarPark::getFrequency(const string &name) const
{
  int n = clientPosition(name);
  if (n != -1)
    return clients[n].frequency;
  else {
    throw ClientDoesNotExist(name);
  }

}

// TODO: to modify
bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    clients.push_back(info);
    return true;
}

// TODO: to modify
bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( !(*it).present) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

// TODO: to modify
bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    clients[pos].frequency++;
    freePlaces--;
    return true;
}

// TODO: to modify
bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


// TODO
InfoCard CarPark::getClientAtPos(unsigned p) const {
  if (p<0 || p >= clients.size())
    throw PositionDoesNotExist(p);
  InfoCard info;
  info.name = clients[p].name;
  info.present = clients[p].present;
  info.frequency = clients[p].frequency;
  return info;
}

// TODO
void CarPark::sortClientsByFrequency() {
  insertionSort(clients);
}

// TODO
void CarPark::sortClientsByName()
{
  for (unsigned int p = 1; p < clients.size(); p++) {
    InfoCard tmp = clients[p];
    int j;
    for (j = p; j > 0 && tmp.cmpName(clients[j - 1]); j--)
      clients[j] = clients[j - 1];
    clients[j] = tmp;
  }
}

// TODO
vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2) {
  sortClientsByFrequency();
  bool add = false;
  vector<string> names;
  for (int i = 0; i < clients.size(); i++) {
    if (clients[i].frequency <= f2)
      add = true;
    if (clients[i].frequency < f1)
      break;
    if (add)
      names.push_back(clients[i].name);
  }
  return names;
}


// TODO
ostream & operator<<(ostream & os, const CarPark & cp)
{
  for (int i = 0; i < cp.getNumClients(); i++){
    os << cp.getClientAtPos(i).name << " | ";
    if (cp.getClientAtPos(i).present)
      os << "Inside | ";
    else
      os << "Outside | ";
    os << "frequency: " << cp.getClientAtPos(i).frequency << " |\n";
  }
  return os;
}
