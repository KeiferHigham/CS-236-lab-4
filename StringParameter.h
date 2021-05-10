#ifndef INC_236LAB2_STRINGPARAMETER_H
#define INC_236LAB2_STRINGPARAMETER_H
#include "Parameter.h"
#include <string>

using std::string;


class StringParameter : public Parameter {

private:

    string stringParam;




public:
    StringParameter(string paramName) {

    stringParam = paramName;
}



virtual string ToString() {
        return stringParam;
    }

    virtual bool IsExpression() {
        return false;
    }

    virtual bool isConstant() {
        return true;
    }


};
#endif //INC_236LAB2_STRINGPARAMETER_H
