#ifndef CALLCENTERAGENT_H_
#define CALLCENTERAGENT_H_

#include "call.h"
#include <string>
#include <queue>
using namespace std;

class CallCenterAgent {
    unsigned idAgent;
    string nameAgent;
    queue<Call *> myWaitingCalls;
public:
    CallCenterAgent(string nm, unsigned id);
    void addCall(Call *c);
    string getName() const;
    queue<Call *> getWaitingCalls() const;
    unsigned getID() const;
    void moveToFront(string codCall1);
    bool operator==(const CallCenterAgent &c);
    void removeCall();
};

#endif //CALLCENTERAGENT_H_
