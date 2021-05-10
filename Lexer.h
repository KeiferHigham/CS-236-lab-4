#ifndef PROJECT1_LEXER_H
#define PROJECT1_LEXER_H
#include <string>
#include <vector>
#include "Token.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"
#include "Id.h"
#include "StringRec.h"
#include "UndefinedString.h"
#include "Comment.h"
#include "UndefinedComment.h"
#include "EndOfFile.h"


using std::vector;

class Lexer {

private:
    std::string fileInput = "";
    // instantiate the matcheratuom objects and add them to vector of machines first
    Automaton* commaFSA = new MatcherAutomaton(",", COMMA);

    vector<Automaton*> automata;
    vector<Token*> tokens;

    // instantiate the matcheratuom objects and add them to vector of machines first

    int lineNum;

public:
    Lexer();
    ~Lexer();

    void Run(std::string input);

    void AddInput(std::string inputLine);


    void FileEnd() {
        EndOfFile Ef = EndOfFile();

        Token* endFile = new Token(EOFF, "",lineNum);
        tokens.push_back(endFile);
    }

    vector<Token*> GetTokens() {
        return tokens;
    }

    void ToString();


};


#endif //PROJECT1_LEXER_H
