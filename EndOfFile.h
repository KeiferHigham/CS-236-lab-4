#ifndef PROJECT1_ENDOFFILE_H
#define PROJECT1_ENDOFFILE_H

#include "Automaton.h"
#include "iostream"
using std::string;

class EndOfFile : public Automaton {


private:

   TokenType tokenName;


public:



    EndOfFile(TokenType token) {
        tokenName = token;
    }
    EndOfFile() {

    }
    virtual Token* CreateToken(std::string& input, int lineNumber) {

        return new Token(tokenName, input, lineNumber);
    }


    virtual int Read(const std::string& input){
        return 0;
    }






};

#endif //PROJECT1_ENDOFFILE_H
