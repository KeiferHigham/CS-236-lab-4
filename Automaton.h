#ifndef PROJECT1_AUTOMATON_H
#define PROJECT1_AUTOMATON_H

#include "Token.h"
#include <string>

class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;
    TokenType typeTok;


public:
    Automaton() {}
    virtual ~Automaton() {}


    // Start the automaton and return the number of characters read
    // read == 0 indicates the input was rejected
    // read > 0 indicates the input was accepted
    virtual int Read(const std::string& input) = 0;
    virtual Token* CreateToken(std::string& input, int lineNumber) {

        return new Token(typeTok, input, lineNumber);
    }

    virtual int NewLinesRead() const { return newLines ; }
};

#endif //PROJECT1_AUTOMATON_H
