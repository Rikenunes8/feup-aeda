#ifndef CALL_H_
#define CALL_H_

#include <string>
using namespace std;

class Call {
    string codeCall;
    unsigned int nifCode;
public:
    Call(string codCall, unsigned nifCod);
    virtual ~Call();
    string getCodeCall () const;
};


class OrderCall: public Call {
    string orderNum;
    string zipCode;
public:
    OrderCall(string codCall, unsigned nifCod, string orderN, string zCode);
    string getZipCode() const;
};


#endif //CALL_H_
