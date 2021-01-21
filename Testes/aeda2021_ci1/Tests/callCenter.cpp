#include "callCenter.h"
#include <iostream>

CallCenter::CallCenter()
{}

list<CallCenterAgent> CallCenter::getAgents() const {
    return agents;
}

void CallCenter::addAgent(const CallCenterAgent &cca) {
    agents.push_back(cca);
}

vector<stack<OrderCall *> >CallCenter::getOrders() const {
    return attendedOrderCalls;
}

void CallCenter::setOrders(vector<stack<OrderCall *> > stOrd1) {
    attendedOrderCalls = stOrd1;
}


//---------------------------------------------------------------------

queue<Call *> CallCenter::removeAgent(string name) {
    queue<Call *> aux;
    for (auto agent:agents) {
        if (agent.getName() == name) {
            aux = agent.getWaitingCalls();
            agents.remove(agent);
            return aux;
        }
    }
    throw NoAgentException();
}


void CallCenter::sortAgents() {
    agents.sort([](const CallCenterAgent &c1, const CallCenterAgent &c2) {
       if (c1.getWaitingCalls().size() == c2.getWaitingCalls().size())
           if (c1.getName() == c2.getName())
               return c1.getID() < c2.getID();
           else
               return c1.getName() < c2.getName();
       else
           return c1.getWaitingCalls().size() > c2.getWaitingCalls().size();
    });
}


bool CallCenter::putInLessBusyAgent(Call * newCall) {
    size_t min = 100;
    int i = 0, iMin = 0;
    if (agents.empty()) return false;

    for (list<CallCenterAgent>::iterator it = agents.begin();it != agents.end();it++) {
        if (it->getWaitingCalls().size() < min) {
            min = it->getWaitingCalls().size();
            iMin = i;
        }
        i++;
    }
    list<CallCenterAgent>::iterator it = agents.begin();
    for (int i = 0; i < iMin;i++) {
        it++;
    }

    it->addCall(newCall);
    return true;
}


void CallCenter::addAgent(string name, unsigned idAgent) {
    CallCenterAgent *c = new CallCenterAgent(name, idAgent);
    for(list<CallCenterAgent>::iterator it = agents.begin();it != agents.end();it++) {
        if (it->getWaitingCalls().size() >= 2) {
            c->addCall(it->getWaitingCalls().front());
            it->removeCall();
        }
    }
    agents.push_back(*c);
}

void CallCenter::addOrder(OrderCall *call1) {
    for (int i = 0; i < attendedOrderCalls.size(); i++) {
        if (attendedOrderCalls[i].top()->getZipCode() == call1->getZipCode()) {
            attendedOrderCalls[i].push(call1);
            return;
        }
    }
    stack<OrderCall*> s;
    s.push(call1);
    attendedOrderCalls.push_back(s);
    return;
}


unsigned CallCenter::processOrderZip(string zip1, unsigned n) {

    for (int i = 0; i < attendedOrderCalls.size(); i++) {
        if (attendedOrderCalls[i].top()->getZipCode() == zip1) {
            unsigned t = 0;
            while (!attendedOrderCalls[i].empty() && t < n) {
                attendedOrderCalls[i].pop();
                t++;
            }
            if (attendedOrderCalls[i].empty()) {
                attendedOrderCalls.erase(attendedOrderCalls.begin()+i);
            }
            return t;
        }
    }
    return 0;
}
