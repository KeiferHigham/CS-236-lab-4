#ifndef PROJECT1_STRINGREC_H
#define PROJECT1_STRINGREC_H

#include <string>
#include <iostream>
#include "Automaton.h"
#include "sstream"
using std::string;


class StringRec : public Automaton {

private:


    TokenType tokenName;



public:


    StringRec(TokenType token) {
        tokenName = token;
    }

    virtual Token* CreateToken(std::string& input, int lineNumber) {
        return new Token(tokenName, input, lineNumber);
    }



    virtual int Read(const std::string& input) {

        newLines = 0;
        int read = 0;
        std::stringstream iss(input);

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
                    newLines++;
                    read++;
                }
                else {
                    read++;
                }
            }
        }

        return 0;



    }





};

#endif //PROJECT1_STRINGREC_H
