#ifndef INC_236LAB3_INTERPRETER_H
#define INC_236LAB3_INTERPRETER_H

#include "relation.h"
#include "Predicate.h"
#include <vector>
#include <string>
#include "Rules.h"
#include "Header.h"
#include "Tuple.h"
#include <map>

using std::string;
using std:: vector;
using std::map;


class Interpreter {




private:

    vector<Predicate> schemesList;
    vector<Predicate> factsList;
    vector<Predicate> queriesList;
    vector<Rule> rulesList;
    vector<Relation> relations;
    vector<Parameter*> tempParamsList;
    Tuple tuple = Tuple();
    vector<Relation> queryResults;
    vector<int> projectIndices;
    vector<string> reNameNames;
    vector<Relation> bodyRelations;
    Relation finalRelationOne = Relation();
    map<string,Relation> relationMap;
    Relation finalRelationTwo = Relation();
    bool tuplesAdded = true;
    int numTimesNotAdded = 0;
    int timesThroughRules = 0;



public:

    Interpreter() {}

    void AddLists(vector<Predicate> schemes, vector<Predicate> facts, vector<Rule> rules, vector<Predicate> queries) {
        schemesList = schemes;
        factsList = facts;
        rulesList = rules;
        queriesList = queries;

    };


    void BuildRelations() {

        for (unsigned int i = 0; i < schemesList.size(); ++i) {
            std::string name = schemesList.at(i).GetId();
            tempParamsList = schemesList.at(i).GetHeaderNames();
            Header *attribute = new Header();

            for (unsigned int j = 0; j < tempParamsList.size(); ++j) {
                string headerName = tempParamsList.at(j)->ToString();
                attribute->AddHeader(headerName);
            }
            Relation nextRelation = Relation(name, attribute);
            relations.push_back(nextRelation);

        }

        for (unsigned int i = 0; i < factsList.size(); ++i) {

            tempParamsList = factsList.at(i).GetHeaderNames();
            for (unsigned int j = 0; j < tempParamsList.size(); ++j) {
                tuple.addToTuple(tempParamsList.at(j)->ToString());

            }
            for (unsigned int k = 0; k < relations.size(); ++k) {
                if (factsList.at(i).GetId() == relations.at(k).GetName()) {
                    relations.at(k).insertTuple(tuple);
                }
            }

            tuple = Tuple();


        }
    }

    void BuildRelationMap() {

        for(unsigned int i = 0; i < relations.size(); ++i) {
           relationMap.insert(std::pair<string,Relation>(relations.at(i).GetName(),relations.at(i)));

        }
    }


        void EvaluateQueries() {

            //implementing function with map

            Relation finalRelation;
            bool printRows = false;
            std::cout << "Query Evaluation" << std::endl;
            for (unsigned int i = 0; i < queriesList.size(); ++i) {
                 printRows = false;
                if (relationMap.find(queriesList.at(i).GetId()) != relationMap.end()) {
                    finalRelation = relationMap[queriesList.at(i).GetId()];
                    vector<Parameter *> paramNames = queriesList.at(i).GetHeaderNames();
                    map<string, int> nonConstants;
                    for (unsigned int k = 0; k < paramNames.size(); ++k) {
                        if (paramNames.at(k)->isConstant()) {
                            // if theres two selects in a row

                            finalRelation = finalRelation.select(k,paramNames.at(k)->ToString());


                        }

                            // only keep rows that have the same value as index k
                        else {

                            // if param is non constant see if matches any other non constants and pass in the index
                            if (nonConstants.find(paramNames.at(k)->ToString()) == nonConstants.end()) {
                                nonConstants.insert(std::pair<string, int>(paramNames.at(k)->ToString(), k));
                                projectIndices.push_back(k);
                                reNameNames.push_back(paramNames.at(k)->ToString());


                            } else {
                               // queryResults.push_back(relationMap[queriesList.at(i).GetId()].select(k,
                                                                                        //             nonConstants[paramNames.at(
                                                                                             //                k)->ToString()]));
                                         finalRelation = finalRelation.select(k, nonConstants[paramNames.at(
                                               k)->ToString()]);
                            }

                        }

                    }
                    if(projectIndices.size() > 0) {
                     //   queryResults.push_back(relationMap[queriesList.at(i).GetId()].project(projectIndices,reNameNames));
                      finalRelation =  finalRelation.project(projectIndices,reNameNames);
                      projectIndices.clear();
                      reNameNames.clear();
                      printRows = true;

                    }

                }
                queryResults.push_back(finalRelation);
                set<Tuple> rows = finalRelation.GetRows();
                if(rows.empty()) {
                    std::cout << queriesList.at(i).ToString() << "? No" << std::endl;
                }
                else {
                    std::cout << queriesList.at(i).ToString() << "? Yes(" << rows.size() << ")" << std::endl;
                    if(printRows) {
                        for (set<Tuple>::iterator iter = rows.begin(); iter != rows.end(); ++iter) {

                            vector<string> tupleValues = iter->GetValues();
                            vector<string> headerNames = finalRelation.GetHeaderNames();
                            std::cout << "  ";
                            for (unsigned l = 0; l < tupleValues.size(); ++l) {
                                std::cout << headerNames.at(l) << "=" << tupleValues.at(l);
                                if (l != tupleValues.size() - 1) {
                                    std::cout << ", ";
                                }


                            }

                            std::cout << std::endl;
                        }
                    }
                }

            }
            // coult just print out the relation that I want right here
            //queryResults.push_back(finalRelation);
          //  PrintQueryResults();
        }




       void EvaluateRules() {

           std::cout << "Rule Evaluation" << std::endl;
           while (numTimesNotAdded != (int)rulesList.size()) {
               numTimesNotAdded = 0;
               timesThroughRules++;
               Relation finalRelation;
               for (unsigned int i = 0; i < rulesList.size(); ++i) {
                     std::cout <<  rulesList.at(i).ToString() << "." << std::endl;
                   vector<Predicate> bodyPredicates = rulesList.at(i).GetBodyPredicates();

                   for (unsigned int j = 0; j < bodyPredicates.size(); ++j) {

                       if (relationMap.find(bodyPredicates.at(j).GetId()) != relationMap.end()) {
                           finalRelation = relationMap[bodyPredicates.at(j).GetId()];
                           vector<Parameter *> paramNames = bodyPredicates.at(j).GetHeaderNames();
                           map<string, int> nonConstants;
                           for (unsigned int k = 0; k < paramNames.size(); ++k) {
                               if (paramNames.at(k)->isConstant()) {
                                   // if theres two selects in a row
                                   finalRelation = finalRelation.select(k, paramNames.at(k)->ToString());
                               }

                                   // only keep rows that have the same value as index k
                               else {

                                   // if param is non constant see if matches any other non constants and pass in the index
                                   if (nonConstants.find(paramNames.at(k)->ToString()) == nonConstants.end()) {
                                       nonConstants.insert(std::pair<string, int>(paramNames.at(k)->ToString(), k));
                                       projectIndices.push_back(k);
                                       reNameNames.push_back(paramNames.at(k)->ToString());


                                   } else {
                                       // queryResults.push_back(relationMap[queriesList.at(i).GetId()].select(k,
                                       //             nonConstants[paramNames.at(
                                       //                k)->ToString()]));
                                       finalRelation = finalRelation.select(k, nonConstants[paramNames.at(
                                               k)->ToString()]);
                                   }

                               }

                           }
                           if (projectIndices.size() > 0) {
                               //   queryResults.push_back(relationMap[queriesList.at(i).GetId()].project(projectIndices,reNameNames));
                               finalRelation = finalRelation.project(projectIndices, reNameNames);
                               projectIndices.clear();
                               reNameNames.clear();

                           }

                       }
                       bodyRelations.push_back(finalRelation);

                   }
                   // loop through all of the bodyRelations and joing them for each rule and then clear bodyRelations
                   if (bodyRelations.size() > 0) {    // make sure body relation isn't empy
                       finalRelationOne = bodyRelations.at(0);
                       for (unsigned int l = 0; l < bodyRelations.size() - 1; ++l) {

                           finalRelationOne = bodyRelations.at(l).Join(finalRelationOne, bodyRelations.at(l + 1));
                           // finalRelationOne.join(bodyRelations.at(i+1)) either way works

                       }
                   }
                   bodyRelations.clear();

                   vector<Parameter *> headPredNames = rulesList.at(i).GetHeadPredParams();
                   vector<string> relationHeaders = finalRelationOne.GetHeaderNames();
                   vector<string> ProjectColumnNames;
                   vector<int> projectColumnIndices;
                   // project for head predicate headerNAmes on the final relation
                   for (unsigned int v = 0; v < headPredNames.size(); ++v) {
                       ProjectColumnNames.push_back(headPredNames.at(v)->ToString());
                       for (unsigned int u = 0; u < relationHeaders.size(); ++u) {

                           if (headPredNames.at(v)->ToString() == relationHeaders.at(u)) {
                               projectColumnIndices.push_back(u);

                           }

                       }
                   }

                   finalRelationTwo = finalRelationOne.project(projectColumnIndices, ProjectColumnNames);


                   // rename header names to match corresponding relation in the database

                   finalRelationTwo.Rename(relationMap[rulesList.at(i).getHeadPredName()]);

                   // update the relation in database with newTuples from corresponding new Relation

                   tuplesAdded = relationMap[rulesList.at(i).getHeadPredName()].Union(finalRelationTwo);

                   if (!tuplesAdded) {
                       numTimesNotAdded++;
                   }
                   // clear finalRelaitonTwo for now
                   //clear finalRelationOne
                   finalRelationOne = Relation();
                   finalRelationTwo = Relation();

               }
           }

          // PrintEvaluatedRules();

           std::cout << std::endl << "Schemes populated after " << timesThroughRules << " passes";
           std::cout << " through the Rules." << std::endl << std::endl;

            }

            void PrintEvaluatedRules() {

        for(unsigned int i = 0; i < rulesList.size(); ++i) {
            std::cout << rulesList.at(i).ToString() << std::endl;
           std::cout << relationMap[rulesList.at(i).getHeadPredName()].EvaluatedRulesToString();
        }

    }










};

#endif //INC_236LAB3_INTERPRETER_H
