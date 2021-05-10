#include <iostream>
#include <fstream>
#include "Lexer.h"
#include <sstream>
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "Parser.h"
using namespace std;
int main(int argc, char* argv[]) {


    if(argc < 2) {
        cerr << "Please provide the name of the input file";
        return 1;
    }
   // cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);

    if(!in) {
        cout << "Not able to open " << argv[1] << " for input " << endl;
        return 2;
    }

    Lexer inputLexer = Lexer();
    string line = "";
    while(in.peek() != EOF) {
        line.push_back(in.get());
    }

    inputLexer.Run(line);

    if(in.peek() == EOF) {
        inputLexer.FileEnd();
    }

    //inputLexer.ToString();
    std::cout << std::endl;

    vector<Token*> allTokens = inputLexer.GetTokens();



    // get rid of all of the comma tokens
  TokenType commentToken = COMMENT;
    for(unsigned int i = 0; i < allTokens.size(); ++i) {
        if(allTokens.at(i)->GetTokenName() == commentToken) {
            allTokens.erase(allTokens.begin() + i);
            i--;
        }

    }

    // test to make sure comments are being deleted
 /* std::cout << std::endl;
    for(int i = 0; i < allTokens.size(); ++i) {
        std::cout << allTokens.at(i)->GetTokenString() << std::endl;
    }
 */
      Parser parse = Parser(allTokens);


         parse.RunParser();

    return 0;
}
