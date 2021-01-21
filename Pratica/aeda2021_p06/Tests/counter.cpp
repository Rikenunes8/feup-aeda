#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

//TODO
Client::Client() {
    numGifts = rand()%5+1;
}


//TODO
unsigned Client::getNumGifts() const {
    return numGifts;
}


//TODO
Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime = 0;
    nextEnter = rand()%20 +1;
    nextLeave = 0;
    numAttendedClients = 0;
}

//TODO
unsigned Counter::getActualTime() const {
    return actualTime;
}

//TODO
unsigned Counter::getNextEnter() const {
    return nextEnter;
}

//TODO
unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

//TODO
unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

//TODO
unsigned Counter::getNextLeave() const {
    return nextLeave;
}

//TODO
Client & Counter::getNextClient() {
    if (clients.empty())
        throw EmptyQueue();
    return clients.front();
}

//TODO
void Counter::enter()
{
    clients.push(Client());
    nextEnter = actualTime + rand()%20 +1;
    if (clients.size() == 1)
        nextLeave = actualTime + clients.front().getNumGifts()*wrappingTime;
    
    cout << "ENTER" << endl;
    cout << "Actual Time: " << actualTime <<endl;
    cout << "Gifts: " << clients.back().getNumGifts() << endl;
    cout << "Next leave: " << nextLeave << endl << endl;
}

//TODO
void Counter::leave()
{
    if (clients.empty())
        throw EmptyQueue();
    clients.pop();
    numAttendedClients++;
    if (clients.empty())
        nextLeave = actualTime;
    else
        nextLeave = clients.front().getNumGifts()*wrappingTime;

    cout << "LEAVE" << endl;
    cout << "Actual Time: " << actualTime <<endl;
    cout << "Gifts: " << clients.front().getNumGifts() << endl;
    cout << "Next leave: " << nextLeave << endl << endl;
}

//TODO
void Counter:: nextEvent()
{
    if (nextEnter == nextLeave){
        actualTime += nextEnter;
        enter();
        leave();
    }
    else if (nextEnter < nextLeave || nextLeave == actualTime) {
        actualTime += nextEnter;
        enter();
    }
    else {
        actualTime += nextLeave;
        leave();
    }
}


//TODO
ostream & operator << (ostream & out, const Counter & c2)
{
     return out;
}


