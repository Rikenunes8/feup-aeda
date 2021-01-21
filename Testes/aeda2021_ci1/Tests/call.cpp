#include "call.h"

Call::Call(string codCall, unsigned nifCod): codeCall(codCall), nifCode(nifCod)
{ }

Call::~Call()
{ }

string Call::getCodeCall() const {
    return codeCall;
}

OrderCall::OrderCall(string codCall, unsigned nifCod, string orderN, string zCode):
                            Call(codCall, nifCod), orderNum(orderN), zipCode(zCode)
{ }

string OrderCall::getZipCode() const {
    return zipCode;
}
