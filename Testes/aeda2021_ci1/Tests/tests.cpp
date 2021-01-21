#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "callCenterAgent.h"
#include "call.h"
#include "callCenter.h"
#include <string>
#include <queue>
#include <list>

using testing::Eq;
using namespace std;


TEST(test_1, test_a_removeAgent){
    try {
        CallCenter cc;
        CallCenterAgent cca1("joao",1);
        cca1.addCall(new Call("c1", 111));
        CallCenterAgent cca2("paulo",2);
        cca2.addCall(new Call("c2", 222));
        cca2.addCall(new OrderCall("c3", 333, "o1", "4100"));
        cca2.addCall(new OrderCall("c4", 444,"o2","7100"));
        cca2.addCall(new OrderCall("c5", 555, "o3","4400"));
        CallCenterAgent cca3("fernando",3);
        cca3.addCall(new OrderCall("c6", 666,"o4", "3330"));
        cc.addAgent(cca1);
        cc.addAgent(cca2);
        cc.addAgent(cca3);

        EXPECT_THROW(cc.removeAgent("sergio"), NoAgentException);

        queue <Call*> CallC = cc.removeAgent("joao");
        EXPECT_EQ(1, CallC.size());
        EXPECT_EQ(2, cc.getAgents().size());

        CallC.empty();
        CallC = cc.removeAgent("paulo");
        EXPECT_EQ(4, CallC.size());
        EXPECT_EQ(1, cc.getAgents().size());

        CallC.empty();
        CallC = cc.removeAgent("fernando");
        EXPECT_EQ(1, CallC.size());
        EXPECT_EQ(0, cc.getAgents().size());

        EXPECT_THROW(cc.removeAgent("joao"), NoAgentException);
    }
    catch(...) {
        EXPECT_EQ(true,false);
    }
}


TEST(test_1, test_b_sortAgents){
    CallCenter cc;

    cc.sortAgents();
    list<CallCenterAgent> res = cc.getAgents();
    EXPECT_EQ(0, res.size());
    res.clear();

    CallCenterAgent cca1 ("joao",10);
    cca1.addCall(new Call("c1", 111));
    cc.addAgent(cca1);

    CallCenterAgent cca2 ("sergio",22);
    cca2.addCall(new Call("c2", 222));
    cc.addAgent(cca2);

    CallCenterAgent cca3 ("nuno",11);
    cc.addAgent(cca3);

    CallCenterAgent cca4 ("rui",8);
    cca4.addCall(new Call("c4", 444));
    cca4.addCall(new Call("c5", 555));
    cc.addAgent(cca4);

    CallCenterAgent cca5 ("sergio",4);
    cca5.addCall(new Call("c5", 555));
    cc.addAgent(cca5);

    cc.sortAgents();
    res = cc.getAgents();
    EXPECT_EQ(5, res.size());

    if (res.size()==5) {
        EXPECT_EQ("rui", res.front().getName());
        EXPECT_EQ(2, res.front().getWaitingCalls().size());
        res.pop_front();
        EXPECT_EQ("joao", res.front().getName());
        EXPECT_EQ(1, res.front().getWaitingCalls().size());
        res.pop_front();
        EXPECT_EQ("sergio", res.front().getName());
        EXPECT_EQ(4,res.front().getID());
        EXPECT_EQ(1, res.front().getWaitingCalls().size());
        res.pop_front();
        EXPECT_EQ("sergio", res.front().getName());
        EXPECT_EQ(22,res.front().getID());
        EXPECT_EQ(1, res.front().getWaitingCalls().size());
        res.pop_front();
        EXPECT_EQ("nuno", res.front().getName());
        EXPECT_EQ(0, res.front().getWaitingCalls().size());
        res.pop_front();
    }
}


TEST(test_1, test_c_addAgent){
    CallCenter cc;

    CallCenterAgent cca1("joao",111);
    cca1.addCall(new Call("c1", 111));
    cc.addAgent(cca1);

    CallCenterAgent cca2("rui",222);
    cca2.addCall(new Call("c2", 222));
    cca2.addCall(new Call("c3", 333));
    cca2.addCall(new Call("c4", 444));
    cc.addAgent(cca2);

    CallCenterAgent cca3 ("mario",333);
    cca3.addCall(new Call("c5", 555));
    cc.addAgent(cca3);

    cc.addAgent("vasco",444);
    list<CallCenterAgent> res = cc.getAgents();
    EXPECT_EQ(4, res.size());
    if (res.size()==4) {
        CallCenterAgent cca4 = res.back();
        EXPECT_EQ(444, cca4.getID());
        EXPECT_EQ(1, cca4.getWaitingCalls().size());
        EXPECT_EQ("c2", cca4.getWaitingCalls().front()->getCodeCall());
        EXPECT_EQ(1, res.front().getWaitingCalls().size());
        res.pop_front();
        EXPECT_EQ(2, res.front().getWaitingCalls().size());
        EXPECT_EQ("c3", res.front().getWaitingCalls().front()->getCodeCall());
        res.pop_front();
        EXPECT_EQ(1, res.front().getWaitingCalls().size());
    }
}


TEST(test_1, test_d_PutInLessBusyAgent){
    CallCenter cc;

    EXPECT_EQ(false,cc.putInLessBusyAgent(new Call("cF0", 133)));
    EXPECT_EQ(0, cc.getAgents().size());
        
    CallCenterAgent cca1 ("fernando",1);
    cca1.addCall(new Call("c1", 111));
    cca1.addCall(new Call("c2", 222));
    cca1.addCall(new Call("c3", 333));
    cc.addAgent(cca1);
        
    CallCenterAgent cca2 ("joaquim",2);
    cc.addAgent(cca2);

    CallCenterAgent cca3 ("manuel",3);
    cca3.addCall(new Call("c4", 444));
    cca3.addCall(new Call("c5", 555));
    cc.addAgent(cca3);

    CallCenterAgent cca4 ("alexandre",4);
    cca4.addCall(new Call("c7", 777));
    cc.addAgent(cca4);

    EXPECT_EQ(true,cc.putInLessBusyAgent(new Call("cF1", 122)));
    list<CallCenterAgent> agts = cc.getAgents();
    EXPECT_EQ(4,agts.size());
    if (agts.size()==4) {
        queue<Call *> calls1 = agts.front().getWaitingCalls();
        EXPECT_EQ(3, calls1.size());
        agts.pop_front();
        queue<Call *> calls2 = agts.front().getWaitingCalls();
        EXPECT_EQ(1, calls2.size());
        if (calls2.size()==1)
            EXPECT_EQ("cF1", calls2.back()->getCodeCall());
    }

    agts.clear();
    EXPECT_EQ(true,cc.putInLessBusyAgent(new Call("cF2", 133)));
    agts = cc.getAgents();
    EXPECT_EQ(4,agts.size());
    if (agts.size()==4) {
        queue<Call *> calls3 = agts.front().getWaitingCalls();
        EXPECT_EQ(3, calls3.size());
        agts.pop_front();
        calls3 = agts.front().getWaitingCalls();
        EXPECT_EQ(2, calls3.size());
        if (calls3.size()==2)
            EXPECT_EQ("cF2", calls3.back()->getCodeCall());
        agts.pop_front();
        calls3 = agts.front().getWaitingCalls();
        EXPECT_EQ(2, calls3.size());
        agts.pop_front();
        calls3 = agts.front().getWaitingCalls();
        EXPECT_EQ(1, calls3.size());
    }
}


TEST(test_1, test_e_moveToFront) {
    CallCenterAgent cca1("joaquim", 1);

    cca1.moveToFront("cT");
    queue<Call *> res = cca1.getWaitingCalls();
    EXPECT_EQ(0, res.size());

    CallCenterAgent cca2("fernando", 2);
    cca2.addCall(new Call("c1", 111));
    cca2.addCall(new Call("c2", 222));
    cca2.addCall(new Call("c3", 333));

    cca2.moveToFront("c3");
    res = cca2.getWaitingCalls();
    EXPECT_EQ(3, res.size());
    if (res.size() == 3) {
        EXPECT_EQ("c3", res.front()->getCodeCall());
        res.pop();
        EXPECT_EQ("c1", res.front()->getCodeCall());
        res.pop();
        EXPECT_EQ("c2", res.front()->getCodeCall());
    }

    CallCenterAgent cca3 ("fernando",3);
    cca3.addCall(new Call("c1", 111));
    cca3.addCall(new Call("c2", 222));
    cca3.addCall(new Call("c3", 333));
    cca3.moveToFront("cT");
    res = cca3.getWaitingCalls();
    EXPECT_EQ(3,res.size());
    if (res.size()==3) {
        EXPECT_EQ("c1", res.front()->getCodeCall());
        res.pop();
        EXPECT_EQ("c2", res.front()->getCodeCall());
        res.pop();
        EXPECT_EQ("c3", res.front()->getCodeCall());
    }

    CallCenterAgent cca4 ("nuno",4);
    cca4.addCall(new Call("c1", 111));
    cca4.addCall(new Call("c2", 222));
    cca4.addCall(new Call("c3", 333));
    cca4.addCall(new Call("c4", 444));
    cca4.moveToFront("c2");
    res = cca4.getWaitingCalls();
    EXPECT_EQ(4,res.size());
    if (res.size()==4) {
        EXPECT_EQ("c2", res.front()->getCodeCall());
        res.pop();
        EXPECT_EQ("c1", res.front()->getCodeCall());
        res.pop();
        EXPECT_EQ("c3", res.front()->getCodeCall());
        res.pop();
        EXPECT_EQ("c4", res.front()->getCodeCall());
    }
}

TEST(test_1, test_f_addOrder){
    CallCenter cc;
    vector<stack<OrderCall *> > orders;
    stack<OrderCall *> stOrd1;
    stOrd1.push(new OrderCall("c1", 111,"o1","4100"));
    stOrd1.push(new OrderCall("c2", 111,"o2","4100"));
    orders.push_back(stOrd1);
    stack<OrderCall *> stOrd2;
    stOrd2.push(new OrderCall("c3", 111,"o3","4300"));
    orders.push_back(stOrd2);
    cc.setOrders(orders);

    OrderCall *oc1 = new OrderCall("cx", 111,"ox","4000");
    cc.addOrder(oc1);

    orders.clear();
    orders = cc.getOrders();
    EXPECT_EQ(3,orders.size());
    if (orders.size()==3) {
        EXPECT_EQ(2,orders[0].size());
        EXPECT_EQ(1,orders[1].size());
        EXPECT_EQ(1,orders[2].size());
        EXPECT_EQ("cx",orders[2].top()->getCodeCall());
    }

    CallCenter cc2;
    orders.clear();
    stack<OrderCall *> stOrd11;
    stOrd11.push(new OrderCall("c1", 111,"o1","4100"));
    stOrd11.push(new OrderCall("c2", 111,"o2","4100"));
    orders.push_back(stOrd11);
    stack<OrderCall *> stOrd12;
    stOrd12.push(new OrderCall("c3", 111,"o3","4300"));
    orders.push_back(stOrd12);
    cc2.setOrders(orders);

    OrderCall *oc2 = new OrderCall("cy", 111,"oy","4100");
    cc2.addOrder(oc2);

    orders.clear();
    orders = cc2.getOrders();
    EXPECT_EQ(2,orders.size());
    if (orders.size()==2) {
        EXPECT_EQ(3,orders[0].size());
        EXPECT_EQ(1,orders[1].size());
        EXPECT_EQ("cy",orders[0].top()->getCodeCall());
        EXPECT_EQ("c3",orders[1].top()->getCodeCall());
    }
}


TEST(test_1, test_g_processOrderZip){
    CallCenter cc;
    vector<stack<OrderCall *> > orders;
    stack<OrderCall *> stOrd1;
    stOrd1.push(new OrderCall("c1", 111,"o1","4100"));
    stOrd1.push(new OrderCall("c2", 111,"o2","4100"));
    stOrd1.push(new OrderCall("c3", 111,"o3","4100"));
    stOrd1.push(new OrderCall("c4", 111,"o4","4100"));
    orders.push_back(stOrd1);
    stack<OrderCall *> stOrd2;
    stOrd2.push(new OrderCall("c5", 111,"o5","4300"));
    orders.push_back(stOrd2);
    cc.setOrders(orders);

    unsigned numP =  cc.processOrderZip("4100",3);
    EXPECT_EQ(3,numP);

    orders.clear();
    orders = cc.getOrders();
    EXPECT_EQ(2,orders.size());
    if (orders.size()==3) {
        EXPECT_EQ(1,orders[0].size());
        EXPECT_EQ(1,orders[1].size());
        EXPECT_EQ("c1",orders[0].top()->getCodeCall());
        EXPECT_EQ("c5",orders[1].top()->getCodeCall());
    }

    CallCenter cc2;
    orders.clear();
    stack<OrderCall *> stOrd11;
    stOrd11.push(new OrderCall("c1", 111,"o1","4100"));
    orders.push_back(stOrd11);
    stack<OrderCall *> stOrd12;
    stOrd12.push(new OrderCall("c2", 111,"o2","4300"));
    stOrd12.push(new OrderCall("c3", 111,"o3","4300"));
    stOrd12.push(new OrderCall("c4", 111,"o4","4300"));
    stOrd12.push(new OrderCall("c5", 111,"o5","4300"));
    orders.push_back(stOrd12);
    stack<OrderCall *> stOrd13;
    stOrd13.push(new OrderCall("c6", 111,"o6","4000"));
    orders.push_back(stOrd13);
    stack<OrderCall *> stOrd14;
    stOrd14.push(new OrderCall("c7", 111,"o7","2500"));
    orders.push_back(stOrd14);
    cc2.setOrders(orders);

    numP =  cc2.processOrderZip("4300",7);
    EXPECT_EQ(4,numP);

    orders.clear();
    orders = cc2.getOrders();
    EXPECT_EQ(3,orders.size());
    if (orders.size()==3) {
        EXPECT_EQ(1,orders[0].size());
        EXPECT_EQ("c1",orders[0].top()->getCodeCall());
        EXPECT_EQ(1,orders[1].size());
        EXPECT_EQ(1,orders[2].size());
    }
}

