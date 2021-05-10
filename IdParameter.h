#ifndef INC_236LAB2_IDPARAMETER_H
#define INC_236LAB2_IDPARAMETER_H
#include "Parameter.h"
#include <string>

using std::string;

class IDParameter: public Parameter {




private:

    string idName;








public:


    IDParameter(string id) {
      idName = id;
   }

   virtual std::string ToString() {
        return idName;
    }


    virtual bool IsExpression() {
        return false;
    }


    virtual bool isConstant() {
        return false;
    }


};




















#endif //INC_236LAB2_IDPARAMETER_H


