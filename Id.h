#ifndef PROJECT1_ID_H
#define PROJECT1_ID_H

#include <string>
#include <iostream>
#include "Automaton.h"
using std::string;

class Identifier : public Automaton  {

private:
    int read = 0;
    TokenType tokenName;



public:

    Identifier(TokenType token) {
        tokenName = token;

    }

    virtual Token* CreateToken(std::string& input, int lineNumber) {
        return new Token(tokenName, input, lineNumber);
    }


    virtual int Read(const std::string& input) {
        read = 0;

        if(isalpha(input.at(read))) {
            read = read + 1;
            for(unsigned int i = 1; i < input.size() && (isalpha(input.at(i)) || isdigit(input.at(i))); ++i) {
                read++;

            }
        }
        return read;
    }











};

#endif //PROJECT1_ID_H
