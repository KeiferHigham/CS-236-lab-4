#ifndef INC_236LAB2_PREDICATE_H
#define INC_236LAB2_PREDICATE_H

#include "Parameter.h"
#include <string>
#include <vector>
#include <sstream>

using std::vector;
using std::string;

class Predicate {


private:

    vector<Predicate> schemeList;
    vector<Predicate> queriesList;
    vector<Predicate> factList;
    string id;
    vector<Parameter*> param;


public:


    Predicate(string idName, vector<Parameter*> paramNames) {
        id = idName;
        param = paramNames;
    }
    Predicate() {

    }

    std::string GetId() {
        return id;
    }

    std::vector<Parameter*> GetHeaderNames() {
        return param;
    }

    void AddSchemeList(Predicate schemePred) {
        schemeList.push_back(schemePred);
    }

    void AddQueriesList(Predicate queriesPred) {
        queriesList.push_back(queriesPred);
    }

    void AddFactList(Predicate factPred) {
        factList.push_back(factPred);
    }


    string ToString() {
        std::stringstream os;

        os  << id << "(";
        for(unsigned int i  = 0; i < param.size(); ++i) {
            os << param.at(i)->ToString();
            if(i == param.size() - 1) {
                break;
            }
            os << ",";
        }
        os << ")";

        return os.str();
    }





    /*void PrintFacts() {
        std::cout << "Facts(" << factList.size() << "):" << std::endl;
        for(int i = 0; i < factList.size(); ++i) {
            std::cout << factList.at(i).ToString() << "." << std::endl;
        }
    } */

    void PrintQueries() {
        std::cout << "Queries(" << queriesList.size() << "):" << std::endl;
        for(unsigned int i = 0; i < queriesList.size(); ++i) {
            std::cout << queriesList.at(i).ToString() << "?" << std::endl;
        }
    }

















};

#endif //INC_236LAB2_PREDICATE_H
