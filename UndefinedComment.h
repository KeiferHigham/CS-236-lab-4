#ifndef PROJECT1_UNDEFINEDCOMMENT_H
#define PROJECT1_UNDEFINEDCOMMENT_H

#include "Automaton.h"
#include "iostream"

using std::string;


class UndefinedComment : public Automaton {



private:
    TokenType tokenName;



public:

    UndefinedComment(TokenType token) {
        tokenName = token;
    }

    virtual Token* CreateToken(std::string& input, int lineNumber) {
        return new Token(tokenName, input, lineNumber);
    }



    virtual int Read(const std::string& input) {
        std::stringstream iss(input);
        int read = 0;

        if(iss.get() == '#') {
            read++;

            if (iss.peek() == EOF || iss.peek() == '\n') {
                return read;   // its okay for single line comment to hit end of file
            }
            else if(iss.get() == '|') {
                return lineComment(input);
            }
            else {
                read++;
                while(iss.peek() != EOF && iss.peek() != '\n') {
                    iss.get();
                    read++;
                }
                return read;

            }


        }

        return read;

    }

    int lineComment(std::string input) {
        int read = 2;
        string inputRead = input.substr(2,input.size() - 1);
        std::stringstream iss(inputRead);
       newLines = 0;

       if(iss.peek() == '\n') {
           newLines++;
       }
        while(iss.peek() != EOF) {
            char c = iss.get();
            if(iss.peek() == EOF) {
                read++;
                return read;
            }
            if(c == '|' && iss.peek() == '#') {
                read = read + 2;
                return read;
            }
            if(c == '\n') {
                newLines++;
            }
            read++;
        }

        return read;
    }



};

#endif //PROJECT1_UNDEFINEDCOMMENT_H
