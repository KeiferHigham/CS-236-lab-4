#include "Automaton.h"
#include <iostream>

using std::string;


class Comment : public Automaton {

private:

    TokenType token;








public:

    Comment(TokenType tokenName) {
        token = tokenName;
    }

    virtual Token* CreateToken(std::string& input, int lineNumber) {
        return new Token(token, input, lineNumber);
    }



    virtual int Read(const std::string& input) {
        std::stringstream iss(input);
        int read = 0;

        if(iss.get() == '#') {
            read++;
        //   if(iss.peek() == '\n') {
         //      newLines++;
         //  }
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
              //  if(iss.peek() == '\n') {
                //    newLines++;
              //  }
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

        while(iss.peek() != EOF) {
            char c = iss.get();
            if(iss.peek() == EOF) {
               read++;
                return 0;
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

        read = 0;  // I'll want to return the actuall number here of the undefined comment class
        return read; // if it ever gets here then it will hit end of file and will terminate
    }





};

