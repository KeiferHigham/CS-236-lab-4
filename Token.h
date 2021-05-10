#ifndef PROJECT1_TOKEN_H
#define PROJECT1_TOKEN_H

#include <string>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
                MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT,
                UNDEFINED, EOFF};

class Token {
private:
    TokenType type;
    std::string name;
    int tokenLineNum = 0;


public:
    Token(TokenType token, std::string tokenName, int lineNum) {
    type = token;
    name = tokenName;
    tokenLineNum = lineNum;
}

     TokenType GetTokenName() {
        return type;
    }

    std::string GetTokenString() {
        return name;
    }

    std::string GetTokenError() {
       std::stringstream os;
        if(type == COMMA) {
           os << "(COMMA," << "\"" << name << "\"" << "," << tokenLineNum << ")";
            return os.str();
        }
        else if(type == PERIOD) {
            os << "(PERIOD," << "\"" << name << "\"" << "," << tokenLineNum << ")";
        }
        else if(type == Q_MARK) {
            os << "(Q_MARK," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == LEFT_PAREN) {
            os << "(LEFT_PAREN," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == RIGHT_PAREN) {
            os << "(RIGHT_PAREN," << "\"" << name  << "\"," << tokenLineNum << ")";
        }
        else if (type == COLON) {
            os << "(COLON," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == COLON_DASH) {
            os << "(COLON_DASH," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == MULTIPLY) {
            os << "(MULTIPLY," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == ADD) {
            os << "(ADD," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == SCHEMES) {
            os << "(SCHEMES," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == FACTS) {
            os << "(FACTS," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if(type == RULES) {
            os << "(RULES," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == QUERIES) {
            os << "(QUERIES," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == ID) {
            os << "(ID," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == STRING) {
            os << "(STRING," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == UNDEFINED) {
            os << "(UNDEFINED," << "\"" << name << "\"," << tokenLineNum << ")";
        }
        return os.str();
    }

    std::string ToString() {
        std::stringstream os;

        if(type == COMMA) {
            os << "(COMMA" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if(type == PERIOD) {
            os << "(PERIOD" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if(type == Q_MARK) {
            os << "(Q_MARK" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if(type == LEFT_PAREN) {
            os << "(LEFT_PAREN" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if(type == RIGHT_PAREN) {
            os << "(RIGHT_PAREN" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if(type == COLON) {
            os << "(COLON" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if(type == COLON_DASH) {
            os << "(COLON_DASH" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == MULTIPLY) {
            os << "(MULTIPLY" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == ADD) {
            os << "(ADD" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == SCHEMES) {
            os << "(SCHEMES" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == FACTS) {
            os << "(FACTS" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == RULES) {
            os << "(RULES" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == QUERIES) {
            os << "(QUERIES" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == ID) {
            os << "(ID" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == STRING) {
            os << "(STRING" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == COMMENT) {
            os << "(COMMENT" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == UNDEFINED) {
            os << "(UNDEFINED" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        else if (type == EOFF) {
            os << "(EOF" << ",\"" << name << "\"," << tokenLineNum << ")";
        }
        return os.str();

    }


};






#endif //PROJECT1_TOKEN_H
