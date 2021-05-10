#ifndef INC_236LAB2_PARSER_H
#define INC_236LAB2_PARSER_H

#include "Token.h"
#include <string>
#include <iostream>
#include "Parameter.h"
#include "Predicate.h"
#include "Rules.h"
#include <set>
#include <iterator>
#include "IdParameter.h"
#include "ExpressionParameter.h"
#include "StringParameter.h"
#include "relation.h"
#include "Interpreter.h"
using namespace std;
class Parser {

private:
    int index = 0;
    vector<Token *> tokenList;

    std::string tempId;
    std::string tempParam;
    vector<Parameter> tempParameters;
    vector<Parameter*> params; // this will be able to store pointers to different param types

    Predicate predAdd;

    Rule rule;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    std::string expressionOp;
    std::string secondOp;

    vector<string> operatorList;

    vector<Parameter*> expressionParams;

    std::set<std::string> domain;
    Interpreter interpret = Interpreter();




    bool query = false;
    bool failure = false;


public:

    Parser() {

    }

    Parser(vector<Token *> tokens) {
        tokenList = tokens;
    }

    void RunParser() {
        //I'm going to run all of the functions for terminals and nonterminals starting with datalog
        ParseDataLog();
    }

    bool isMatch(TokenType token) {

        std::string tokenName = tokenList.at(index)->GetTokenString();
        if (tokenList.at(index)->GetTokenName() == EOFF) {
          //  std::cout << "Success!" << std::endl;
            return true;
        } else if (token == tokenList.at(index)->GetTokenName()) {
            index++;
            return true;
        } else {
            throw tokenList.at(index);
        }
    }


    void ParseDataLog() {

        try {
            /* datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList
            * RULES COLON ruleList QUERIES COLON query queryList EOF */
            isMatch(SCHEMES);
            isMatch(COLON);
            ParseScheme();
            ParseSchemeList();
            isMatch(FACTS);
            isMatch(COLON);
            ParseFactList();
            isMatch(RULES);
            isMatch(COLON);
            ParseRuleList();
            isMatch(QUERIES);
            isMatch(COLON);
            ParseQuery();
            ParseQueryList();
            isMatch(EOFF);
        } catch (Token *errorToken) {
            std::cout << "Failure!" << std::endl << "  " << errorToken->GetTokenError() << std::endl;
            failure = true;
        }

        if(!failure) {
          //  PrintSchemes();
          //  PrintFacts();
          //  PrintRules();
          //  PrintQueries();
          //  PrintDomain();
            interpret.AddLists(schemes, facts, rules, queries);
            interpret.BuildRelations();
            interpret.BuildRelationMap();
            interpret.EvaluateRules();
            interpret.EvaluateQueries();
        }


    }

    void ParseScheme() {
        string error = "error on line 78";
        //scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
        // check if equal to first set
        if (tokenList.at(index)->GetTokenName() == ID) {
            std::string tokenString = tokenList.at(index)->GetTokenString();
            tempId = tokenString; // identifier for schemesList
            isMatch(ID);

            isMatch(LEFT_PAREN);
            if (tokenList.at(index)->GetTokenName() == ID) {
             //   Parameter firstParam = Parameter(
             //           tokenList.at(index)->GetTokenString());// create first parameter object right here
             //   tempParameters.push_back(firstParam); // push onto parameter vector
                Parameter* firstParam1 = new IDParameter(tokenList.at(index)->GetTokenString());
                params.push_back(firstParam1);

            }
            isMatch(ID);
            ParseIdList();
            isMatch(RIGHT_PAREN);
           /* Predicate nextPred = Predicate(tempId, tempParameters);
            //Predicate predAdd;        // create new object using the empty constructor
            schemes.push_back(nextPred);   // add nextPred to vector of schemes
            tempId = "";                       //
            tempParameters.clear();
            */
           Predicate nextPred1 = Predicate(tempId, params);
           schemes.push_back(nextPred1);
           tempId = "";
           params.clear();

            // I need to clear the tempVector here

            // add that predicate object to vector of schemes using addSchemesList function
        }
            //if not equal to either throw an exception
        else {
            throw tokenList.at(index);
        }
    }


    void ParseIdList() {

        //idList  	-> 	COMMA ID idList | lambda
        if (tokenList.at(index)->GetTokenName() == COMMA) {
            isMatch(COMMA);
            if (tokenList.at(index)->GetTokenName() == ID) {
              //  Parameter nextParam = Parameter(tokenList.at(
              //          index)->GetTokenString());// create a parameter object takes in string and token type in constructor
              //  tempParameters.push_back(nextParam);
              Parameter* nextParam1 = new IDParameter(tokenList.at(index)->GetTokenString());
              params.push_back(nextParam1);
            }
            isMatch(ID);
            ParseIdList();
            return;
        } else if (tokenList.at(index)->GetTokenName() == RIGHT_PAREN) {
            return;
        } else {
            throw tokenList.at(index);

        }

    }

    void ParseSchemeList() {
        //schemeList	->	scheme schemeList | lambda
        if (tokenList.at(index)->GetTokenName() == ID) {
            ParseScheme();
            ParseSchemeList();
            return;
        } else if (tokenList.at(index)->GetTokenName() == FACTS) {
            return;
        } else {
            throw tokenList.at(index);
            return;
        }

    }

    void ParseFactList() {
        //factList	->	fact factList | lambda
        if (tokenList.at(index)->GetTokenName() == ID) {
            ParseFact();
            ParseFactList();
            return;
        } else if (tokenList.at(index)->GetTokenName() == RULES) {
            return;
        } else {
            throw tokenList.at(index);
            return;
        }
    }

    void ParseRuleList() {
        //ruleList	->	rule ruleList | lambda
        if (tokenList.at(index)->GetTokenName() == ID) {
            ParseRule();
            ParseRuleList();
            //   rules.push_back(rule);
            return;
        } else if (tokenList.at(index)->GetTokenName() == QUERIES) {
            return;
        } else {
            throw tokenList.at(index);
            return;
        }
    }


    void ParseRule() {
        ParseHeadPredicate();
        isMatch(COLON_DASH);
        ParsePredicate();
        ParsePredicateList();
        rules.push_back(rule);
        params.clear();
       rule = Rule();
        // reset rule so its new object
        isMatch(PERIOD);

    }

    void ParseHeadPredicate() {
        if (tokenList.at(index)->GetTokenName() == ID) {
            tempId = tokenList.at(index)->GetTokenString();
            isMatch(ID);
            isMatch(LEFT_PAREN);
            isMatch(ID);
            // create a parameter right here
           // Parameter firstParam = Parameter(tokenList.at(index - 1)->GetTokenString());
           // tempParameters.push_back(firstParam);
              Parameter* firstParam1 = new IDParameter(tokenList.at(index - 1)->GetTokenString());
              params.push_back(firstParam1);
            ParseIdList();
            isMatch(RIGHT_PAREN);
           // Predicate headPred = Predicate(tempId, tempParameters);
           Predicate headPred1 = Predicate(tempId, params);
            rule.SetHead(headPred1);  // headrule is head predicate used to pushback other predicates onto vector
           // tempParameters.clear();
           // tempId = "";
           params.clear();
           tempId = "";
            return;
        } else {
            throw tokenList.at(index);

        }
    }

    void ParsePredicate() {
        // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
        if (tokenList.at(index)->GetTokenName() == ID) {
            tempId = tokenList.at(index)->GetTokenString();
            isMatch(ID);
            isMatch(LEFT_PAREN);
            ParseParameter();
            ParseParameterList();
            isMatch(RIGHT_PAREN);
           // Predicate nextPred = Predicate(tempId, tempParameters);
              Predicate nextPred1 = Predicate(tempId, params);

            if (query) {
                queries.push_back(nextPred1);
            } else {
                rule.AddToBody(nextPred1);
            }
          //  tempId = "";
          //  tempParameters.clear();
              tempId = "";
              params.clear();
            // use head predicate to push back here head predicate needs to be private variable though
            return;
        } else {
            throw tokenList.at(index);

        }
    }

    void ParsePredicateList() {
        if (tokenList.at(index)->GetTokenName() == COMMA) {
            isMatch(COMMA);
            ParsePredicate();
            ParsePredicateList();
        } else if (tokenList.at(index)->GetTokenName() == PERIOD) {
            return;
        } else {
            throw tokenList.at(index);
            return;
        }

    }

    void ParseParameter() {
        // parameter	->	STRING | ID | expression

        if (tokenList.at(index)->GetTokenName() == STRING) {
            isMatch(STRING);
           // Parameter para = Parameter(tokenList.at(index - 1)->GetTokenString());
           // tempParameters.push_back(para);

              Parameter* para1 = new StringParameter(tokenList.at(index - 1)->GetTokenString() );
              params.push_back(para1);

            return;
        } else if (tokenList.at(index)->GetTokenName() == ID) {
            isMatch(ID);
           // Parameter nextPara = Parameter(tokenList.at(index - 1)->GetTokenString());
           // tempParameters.push_back(nextPara);
            Parameter* nextPara1 = new IDParameter(tokenList.at(index - 1)->GetTokenString() );
            params.push_back(nextPara1);

            return;
        } else {
            ParseExpression();
            return;
        }
    }

    void ParseParameterList() {
        if (tokenList.at(index)->GetTokenName() == COMMA) {
            isMatch(COMMA);
            ParseParameter();
            ParseParameterList();
            return;
        } else if (tokenList.at(index)->GetTokenName() == RIGHT_PAREN) {
            return;
        } else {
            throw tokenList.at(index);
            return;
        }
    }

    void ParseExpression() {
        //  expression	->	LEFT_PAREN parameter operator parameter RIGHT_PAREN

        if (tokenList.at(index)->GetTokenName() == LEFT_PAREN) {
            isMatch(LEFT_PAREN);
            ParseParameter();
                Parameter *nextParam = params.at(params.size() - 1);
                params.pop_back();
                ParseOperator();
                ParseParameter();
                Parameter *nextParam2 = params.at(params.size() - 1);
                params.pop_back();
                isMatch(RIGHT_PAREN);
                Parameter *expressionParam = new ExpressionParameter(nextParam,
                                                                     operatorList.at(operatorList.size() - 1),
                                                                     nextParam2);
                params.push_back(expressionParam);
                operatorList.pop_back();


           // Predicate nextPred = Predicate(tempId, tempParameters);
            //tempId = "";
           // tempParameters.clear();


           // Predicate nextPred1 = Predicate(tempId, params);
           // rule.AddToBody(nextPred1);
            expressionOp = "";
            return;
        } else {
            throw tokenList.at(index);
            return;
        }
    }

    void ParseOperator() {
        //  operator	->	ADD | MULTIPLY
        if (tokenList.at(index)->GetTokenName() == ADD) {
            isMatch(ADD);
          //  Parameter param = Parameter(tokenList.at(index - 1)->GetTokenString());
          //  tempParameters.push_back(param);

              operatorList.push_back(tokenList.at(index - 1)->GetTokenString());
            return;
          }
        else if(tokenList.at(index)->GetTokenName() == MULTIPLY) {
            isMatch(MULTIPLY);
            //  Parameter param2 = Parameter(tokenList.at(index - 1)->GetTokenString());
            //  tempParameters.push_back(param2);
            operatorList.push_back(tokenList.at(index - 1)->GetTokenString());

            return;
        } else {
            throw tokenList.at(index);
            return;
        }
    }

    void ParseQuery() {
        //  query	        ->      predicate Q_MARK
        query = true;
        ParsePredicate();
        isMatch(Q_MARK);
        return;

    }

    void ParseQueryList() {
        //queryList	->	query queryList | lambda
        if (tokenList.at(index)->GetTokenName() == ID) {
            ParseQuery();
            ParseQueryList();
            return;

        } else if (tokenList.at(index)->GetTokenName() == EOFF) {
            return;
        } else {
            throw tokenList.at(index);
        }

    }

    void ParseFact() {
        //fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
        if (tokenList.at(index)->GetTokenName() == ID) {
            tempId = tokenList.at(index)->GetTokenString();
            isMatch(ID);
            isMatch(LEFT_PAREN);
            isMatch(STRING);
           // Parameter nextParam = Parameter(tokenList.at(index - 1)->GetTokenString());
            std::string factString = tokenList.at(index - 1)->GetTokenString();
            //tempParameters.push_back(nextParam);
            Parameter* nextParam1 = new StringParameter(tokenList.at(index - 1)->GetTokenString());
            params.push_back(nextParam1);
            domain.insert(factString);
            ParseStringList();
            isMatch(RIGHT_PAREN);
            isMatch(PERIOD);
           // Predicate nextPred = Predicate(tempId, tempParameters);
           Predicate nextPred1 = Predicate(tempId,params);
            //Predicate predAdd;        // create new object using the empty constructor
            facts.push_back(nextPred1);   // add nextPred to vector of schemes
            tempId = "";                       //
           // tempParameters.clear();
           params.clear();
            return;
        } else {
            throw tokenList.at(index);
        }
    }

    void ParseStringList() {
        //  stringList	-> 	COMMA STRING stringList | lambda

        if (tokenList.at(index)->GetTokenName() == COMMA) {
            isMatch(COMMA);
            isMatch(STRING);
            std::string factString = tokenList.at(index - 1)->GetTokenString();
            domain.insert(factString);
           // Parameter param = Parameter(tokenList.at(index - 1)->GetTokenString());
          //  tempParameters.push_back(param);
              Parameter* param1 = new StringParameter(tokenList.at(index - 1)->GetTokenString());
              params.push_back(param1);
            ParseStringList();
            return;
        } else if (tokenList.at(index)->GetTokenName() == RIGHT_PAREN) {
            return;
        } else {
            throw tokenList.at(index);
        }

    }

    void PrintSchemes() {
        std::cout << "Schemes(" << schemes.size() << "):" << std::endl;
        for (unsigned int i = 0; i < schemes.size(); ++i) {
            std::cout << "  " << schemes.at(i).ToString() << std::endl;
        }
    }

    void PrintFacts() {
        std::cout << "Facts(" << facts.size() << "):" << std::endl;
        for(unsigned int i = 0; i < facts.size(); ++i) {
            std::cout << "  " << facts.at(i).ToString() << "." << std::endl;
        }
    }

    void PrintRules() {
        std::cout << "Rules(" << rules.size() << "):" << endl;
        for(unsigned int i = 0; i < rules.size(); ++i) {

            std::cout << "  " << rules.at(i).ToString() << "." << std::endl;
        }
    }

    void PrintQueries() {
        std::cout << "Queries(" << queries.size() << "):" << endl;
        for(unsigned int i = 0; i < queries.size(); ++i) {

            std::cout << "  " << queries.at(i).ToString() << "?" << std::endl;
        }
    }

    void PrintDomain() {

        std::set<std::string>::iterator iter;
        std::cout << "Domain(" << domain.size() << "):" << std::endl;
    for(iter = domain.begin(); iter != domain.end(); ++iter) {
        std::cout << "  " << *iter << std::endl;

    }

}
    // check if current token is equal to first set



  /*  datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList
   * RULES COLON ruleList QUERIES COLON query queryList EOF

    schemeList	->	scheme schemeList | lambda
            factList	->	fact factList | lambda
            ruleList	->	rule ruleList | lambda
            queryList	->	query queryList | lambda

            scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
            fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
            query	        ->      predicate Q_MARK

    headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
            predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN

            predicateList	->	COMMA predicate predicateList | lambda
            parameterList	-> 	COMMA parameter parameterList | lambda
            stringList	-> 	COMMA STRING stringList | lambda
            idList  	-> 	COMMA ID idList | lambda

            parameter	->	STRING | ID | expression
            expression	->	LEFT_PAREN parameter operator parameter RIGHT_PAREN
            operator	->	ADD | MULTIPLY


*/


};

#endif //INC_236LAB2_PARSER_H
