#include "callCenterAgent.h"
#include <string>
#include <iostream>

using namespace std;

CallCenterAgent::CallCenterAgent(string nm, unsigned id): nameAgent(nm),idAgent(id)
{}

string CallCenterAgent::getName() const{
    return nameAgent;
}

unsigned  CallCenterAgent::getID() const {
    return idAgent;
}

queue<Call *> CallCenterAgent::getWaitingCalls() const {
    return myWaitingCalls;
}

void CallCenterAgent::addCall(Call *c) {
    myWaitingCalls.push(c);
}


//---------------------------------------------------------------------

void CallCenterAgent::moveToFront(string codCall1) {
    Call* c = nullptr;
    int n = myWaitingCalls.size();
    for (int i = 0; i < n; i++) {
        if (myWaitingCalls.front()->getCodeCall() != codCall1) {
            myWaitingCalls.push(myWaitingCalls.front());
        }
        else {
            c = myWaitingCalls.front();
        }
        myWaitingCalls.pop();
    }
    if (c != nullptr) {
        myWaitingCalls.push(c);
        for (int i = 0; i < n-1; i++) {
            myWaitingCalls.push(myWaitingCalls.front());
            myWaitingCalls.pop();
        }
    }
}

bool CallCenterAgent::operator==(const CallCenterAgent &c) {
    return idAgent == c.getID();
}

void CallCenterAgent::removeCall() {
    myWaitingCalls.pop();
}

