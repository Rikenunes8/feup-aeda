#ifndef CALLCENTER_H_
#define CALLCENTER_H_

#include "callCenterAgent.h"
#include "call.h"
#include <queue>
#include <list>
#include <stack>

class CallCenter {
    list<CallCenterAgent> agents;
    vector<stack<OrderCall *> > attendedOrderCalls;
public:
    CallCenter();
    vector<stack<OrderCall *> > getOrders() const;
    void setOrders(vector<stack<OrderCall *> > stOrd1);
    void addAgent(const CallCenterAgent &cca);
    void sortAgents();
    list<CallCenterAgent> getAgents() const;
    queue<Call *> removeAgent (string name);
    void addAgent(string name, unsigned idAgent);
    bool putInLessBusyAgent(Call *newCall);
    void addOrder(OrderCall *call1);
    unsigned processOrderZip(string zip1, unsigned n);
};

class NoAgentException {};


#endif //CALLCENTER_H_
