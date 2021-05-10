#ifndef PROJECT1_UNDEFINEDSTRING_H
#define PROJECT1_UNDEFINEDSTRING_H
#include <iostream>
#include <string>
#include "Automaton.h"

using std::string;
class UndefinedString : public Automaton {

private:

    TokenType tok;




public:

    UndefinedString(TokenType tokenName) {
        tok = tokenName;
    }

    virtual Token* CreateToken(std::string& input, int lineNumber) {
        return new Token(tok, input, lineNumber);
    }




    virtual int Read(const std::string& input) {
        std::stringstream iss(input);
        newLines = 0;
        int read = 0;
        if(iss.get() == '\'') {     // 'hell''s'
            read++;

            while(iss.peek() != EOF) {
                char c = iss.get();


                if(c == '\'' && iss.peek() == '\'') {
                    read = read + 2;
                    iss.get(); // changed from char b = iss.get()
                }

                else if(c == '\'' && iss.peek() != '\'') {
                    read++;
                    return read;
                }
                else if(c == '\n') {
                    read++;
                    newLines++;
                }
                else {
                    read++;
                }
            }
            return read;
        }
        return 0;

        }


















};

#endif //PROJECT1_UNDEFINEDSTRING_H
