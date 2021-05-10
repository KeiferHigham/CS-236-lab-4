#ifndef PROJECT1_MATCHERAUTOMATON_H
#define PROJECT1_MATCHERAUTOMATON_H

#include "Automaton.h"

class MatcherAutomaton : public Automaton {

private:
    std::string matcher;
    TokenType tokenName;

public:
    MatcherAutomaton(std::string toMatch, TokenType token ){
        matcher = toMatch;
        tokenName = token;
    }

    virtual Token* CreateToken(std::string& input, int lineNumber) {
        return new Token(tokenName, input, lineNumber);
    }

    virtual int Read(const std::string& input) {
        bool isMatch = true;
        int inputRead = 0;
        for(int i = 0; i < (int)matcher.size() && isMatch; ++i) {
            if(input[i] != matcher[i]) {
                isMatch = false;
            }
        }
        if (isMatch) {
            inputRead = matcher.size();
        }
        return inputRead;
    }





};

#endif //PROJECT1_MATCHERAUTOMATON_H
