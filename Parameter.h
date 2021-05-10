#ifndef INC_236LAB2_PARAMETER_H
#define INC_236LAB2_PARAMETER_H
#include <string>


class Parameter {

private:
    std::string paramName;



public:


    virtual ~Parameter() {}

  /*  Parameter(std::string param) {
        paramName = param;
    }
    */

  virtual std::string ToString() = 0;

   /* std::string ToString() {
        return paramName;
    }



*/
   virtual bool IsExpression () = 0;

   virtual bool isConstant() = 0;





};

#endif //INC_236LAB2_PARAMETER_H
