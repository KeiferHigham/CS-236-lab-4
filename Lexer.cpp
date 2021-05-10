#include "Lexer.h"
#include <iostream>

using namespace std;


Lexer::Lexer() {
    //add all of the keyword machines first
automata.push_back(commaFSA); // this does the same thing
automata.push_back(new MatcherAutomaton(".", PERIOD));
automata.push_back(new MatcherAutomaton("?", Q_MARK));
automata.push_back(new MatcherAutomaton("(", LEFT_PAREN));
automata.push_back(new MatcherAutomaton(")", RIGHT_PAREN));
automata.push_back(new MatcherAutomaton(":", COLON));
automata.push_back(new MatcherAutomaton(":-",COLON_DASH));
automata.push_back(new MatcherAutomaton("*", MULTIPLY));
automata.push_back(new MatcherAutomaton("+", ADD));
automata.push_back(new MatcherAutomaton("Schemes", SCHEMES));
automata.push_back(new MatcherAutomaton("Facts",FACTS));
automata.push_back(new MatcherAutomaton("Rules",RULES));
automata.push_back(new MatcherAutomaton("Queries", QUERIES));
automata.push_back(new Identifier(ID));
automata.push_back(new StringRec(STRING));
automata.push_back(new UndefinedString(UNDEFINED));
automata.push_back(new Comment(COMMENT));
automata.push_back(new UndefinedComment(UNDEFINED));
automata.push_back(new EndOfFile(EOFF));


}
Lexer::~Lexer() {

    // need to delete dynamically allocated memory here!!

}


void Lexer::AddInput(std::string inputLine) {
    fileInput = inputLine;

}

void Lexer::Run(std::string input) {
    int lineNumber = 1;
    int inputRead = 0;

    while (input.size() > 0) {

        int maxRead = 0;
        Automaton *maxAutomaton = automata.at(0);

        for (unsigned int i = 0; i < automata.size(); ++i) {
            inputRead = automata.at(i)->Read(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }

        if (maxRead > 0) {
            Token *newToken;
            string tokenName = input.substr(0, maxRead);
            newToken = maxAutomaton->CreateToken(tokenName, lineNumber);
            lineNumber = maxAutomaton->NewLinesRead() + lineNumber;
            tokens.push_back(newToken);
        }

        else if(isspace(input.at(0)) || input.at(0) == '\n') {
            if(input.at(0) == '\n') {
                lineNumber = lineNumber + 1;
            }
            maxRead = 1;

        }

        else {
            maxRead = 1;
            string invalidToken = input.substr(0, maxRead);
            Token *newToken = new Token(UNDEFINED, invalidToken,lineNumber);
            tokens.push_back(newToken);

        }
        input = input.substr(maxRead, input.size() - 1);
    }

lineNum = lineNumber;

}

void Lexer::ToString() {
   for(unsigned int i = 0; i < tokens.size(); ++i) {
        std::cout << tokens.at(i)->ToString() << std::endl;
    }
    std::cout << "Total Tokens = " << tokens.size();

}










