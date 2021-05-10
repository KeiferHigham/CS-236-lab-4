#ifndef INC_236LAB2_EXPRESSIONPARAMETER_H
#define INC_236LAB2_EXPRESSIONPARAMETER_H
#include "Parameter.h"
#include "IdParameter.h"
#include "StringParameter.h"
#include <string>
#include <sstream>

using std::string;



class ExpressionParameter : public Parameter {



private:
std::string expressionOperator;
Parameter* leftParam;
Parameter* rightParam;




public:

    ExpressionParameter(Parameter* left, std::string op, Parameter* right) {
      leftParam = left;
      expressionOperator = op;
      rightParam = right;

}


virtual std::string ToString() {
        std::stringstream os;

        if(rightParam->IsExpression()) {
            os << "(" << leftParam->ToString() << expressionOperator << rightParam->ToString() << ")";

            return os.str();
        }
        os << "(" << leftParam->ToString() << expressionOperator << rightParam->ToString() << ")";
        return os.str();

    }

    virtual bool IsExpression() {
        return true;
    }

    virtual bool isConstant() {
        return false;
    }








};

#endif //INC_236LAB2_EXPRESSIONPARAMETER_H
