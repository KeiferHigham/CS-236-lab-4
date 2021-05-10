#ifndef INC_236LAB3_RELATION_H
#define INC_236LAB3_RELATION_H
#include <string>
#include <set>
#include "Tuple.h"
#include "Header.h"
#include <iterator>

using std::string;
using std::set;

class Relation {


private:

     string name;
    Header* header;
    set<Tuple> rows;
    vector<int> indicesAdded;   // contains the unique indices
    vector<int> matchOne;    // contains the indices of matching for first relation
    vector<int> matchTwo;    // contains the indices that match for second relation
    string output = "";
    vector<string> outputs;
    int numToStringCalled = 0;
public:

    Relation(string& schemeName, Header* theHeader) {
        header = theHeader;
        name = schemeName;
    }
    Relation() {

    }



    vector<string> GetHeaderNames() {
        return header->GetAttributeNames();
    }

    void insertTuple(Tuple nextTuple) {
     rows.insert(nextTuple);
}
     std::string GetName() {
        return name;
    }
    void AddHeader(string headName) {
        header->AddHeader(headName);
    }

    set<Tuple> GetRows() {
        return rows;
    }

    Relation select(int index, std::string value) {

        Relation temp = Relation(name, header);

        for(set<Tuple>::iterator iter = rows.begin(); iter != rows.end(); ++iter) {

            vector<string> tupleValues = iter->GetValues(); // returning the rows values of each tuple
            // trying to determine which tuple we want to keep from list of tuples rows
            if (tupleValues.at(index) == value) {
                temp.insertTuple(*iter);
            }

        }

        return temp;

    }


    Relation select(int index1, int index2) {

        Relation temp = Relation(name, header);

        for(set<Tuple>::iterator iter = rows.begin(); iter != rows.end(); ++iter) {

            vector<string> tupleValues = iter->GetValues(); // returning the rows values of each tuple
            // trying to determine which tuple we want to keep from list of tuples rows
            if (tupleValues.at(index1) == tupleValues.at(index2)) {
                temp.insertTuple(*iter);
            }

        }


        return temp;
    }

    Relation project(vector<int> indices, vector<string> headerReNames) {

        Header* nextHeader = new Header();

        vector<string> oldHeaderNames = header->GetAttributeNames();

        for(unsigned int i = 0; i < indices.size(); ++i) {

            nextHeader->AddHeader(oldHeaderNames.at(indices.at(i)));
        }

         nextHeader->UpdateNames(headerReNames);

        Relation temp = Relation(name, nextHeader);


        // I only want to keep the the right index of each row
        vector<string> newRow;

        for(set<Tuple>::iterator iter = rows.begin(); iter != rows.end(); ++iter) {

            vector<string> tupleValues = iter->GetValues(); // returning the rows values of each tuple
            Tuple nextTuple = Tuple();
            for(unsigned int i = 0; i < indices.size(); ++i) {

                nextTuple.addToTuple(tupleValues.at(indices.at(i)));

            }
            temp.insertTuple(nextTuple);


        }
        return temp;



    }

    void Rename(Relation relation) {
        vector<string> headerNames = relation.GetHeaderNames();
          name = relation.GetName();
        header->UpdateNames(headerNames);
    }

    bool Union(Relation relation)  {

        set<Tuple> nextRows = relation.GetRows();
        std::set<Tuple>::iterator iter;
        std::set<Tuple>::iterator iterTwo;
        int numTuples = rows.size();
        bool tuplesAdded = true;
        vector<string> headerNames = relation.GetHeaderNames();
        int sizeBefore = 0;
        int sizeAfter = 0;
        for(iter = nextRows.begin(); iter != nextRows.end(); ++iter) {

            sizeBefore = rows.size();
            rows.insert(*iter);
            sizeAfter = rows.size();
            if (sizeAfter > sizeBefore) {
                vector<string> rowValues = iter->GetValues();
                output = output + "  ";
                for (unsigned int i = 0; i < rowValues.size(); ++i) {
                    output = output + headerNames.at(i) + "=" + rowValues.at(i);
                    if (i != rowValues.size() - 1) {
                        output = output + ", ";
                    }
                }
                output = output + "\n";
            }


        }
        std::cout << output;
        output = "";


          if(numTuples >= (int)rows.size()) {
              tuplesAdded = false;
          }
          return tuplesAdded;
    }

    string EvaluatedRulesToString() {
        numToStringCalled++;
        return outputs[numToStringCalled - 1];
    }

    Relation Join(Relation relationOne, Relation relationTwo) {

        // joins all of the headers with first relation with unique headers from second
        Relation nextRelation = joinHeaders(relationOne, relationTwo);

        set<Tuple> firstTuples = relationOne.GetRows();
        set<Tuple> secondTuples = relationTwo.GetRows();

        std::set<Tuple>::iterator iter;
        std::set<Tuple>::iterator secondIter;


        Tuple tempTuple = Tuple();


          bool match = true;
        for(iter = firstTuples.begin(); iter != firstTuples.end(); ++iter) {
            vector<string> firstTupleNames = iter->GetValues();

            for(secondIter = secondTuples.begin(); secondIter != secondTuples.end(); ++secondIter) {
                vector<string> secondTupleNames = secondIter->GetValues();
                match = true;
                 if(matchOne.size() > 0) {
                     for (unsigned int i = 0; i < matchOne.size(); ++i) {
                         if (firstTupleNames.at(matchOne.at(i)) != secondTupleNames.at(matchTwo.at(i))) {
                             match = false;
                         }
                     }
                     if (match) {
                         // add all of the tupls from first relation
                         for (unsigned int i = 0; i < firstTupleNames.size(); ++i) {
                             tempTuple.addToTuple(firstTupleNames.at(i));
                         }
                         // now add all unique tuples from second relation

                         for (unsigned int i = 0; i < indicesAdded.size(); ++i) {
                             tempTuple.addToTuple(secondTupleNames.at(indicesAdded.at(i)));
                         }
                         // add newly generated Tuple to new relation object and then clear
                         nextRelation.insertTuple(tempTuple);
                         tempTuple = Tuple();

                     }
                 }
                // add all tuples from both relations
                else {
                    for(unsigned int i = 0; i < firstTupleNames.size(); ++i) {
                        tempTuple.addToTuple(firstTupleNames.at(i));
                    }
                    // now add all unique tuples from second relation

                    for(unsigned int i = 0; i < secondTupleNames.size(); ++i) {
                        tempTuple.addToTuple(secondTupleNames.at(i));
                    }
                    nextRelation.insertTuple(tempTuple);
                    tempTuple = Tuple();
                }
            }


        }

         return nextRelation;


    }

    Relation joinHeaders(Relation firstRelation, Relation secondRelation) {

        vector<string> firstHeaderNames = firstRelation.GetHeaderNames();
        vector<string> secondHeaderNames = secondRelation.GetHeaderNames();
        Relation tempRelation = Relation();
        Header* nextHeader = new Header();

        if(indicesAdded.size() > 0) {
            indicesAdded.clear();
        }

        if(matchOne.size() > 0) {
            matchOne.clear();
            matchTwo.clear();
        }


        // add all of the first relations headers first
        for(unsigned int i = 0; i < firstHeaderNames.size(); ++i) {
            nextHeader->AddHeader(firstHeaderNames.at(i));
        }

        bool unique = true;
        // only add headers from second relation if they are unique

        for(unsigned int i = 0; i < secondHeaderNames.size(); ++i) {
            unique = true;
            for(unsigned int j = 0; j < firstHeaderNames.size(); ++j) {

                if(secondHeaderNames.at(i) == firstHeaderNames.at(j)) {
                    unique = false;
                   // push back int onto vector for first mtches j
                   // push abck int i onto another vector for the isjoinable function
                    // add all of the tuples from first relation
                    matchOne.push_back(j);
                    matchTwo.push_back(i);

                }


            }
            if(unique) {
                nextHeader->AddHeader(secondHeaderNames.at(i));
                indicesAdded.push_back(i);  // this will help to know where to add tuple from second relation
            }


        }
        tempRelation.header = nextHeader;

        return tempRelation;

    }







};

#endif //INC_236LAB3_RELATION_H
