#ifndef INC_236LAB2_RULES_H
#define INC_236LAB2_RULES_H

#include "Predicate.h"
#include <vector>
#include <sstream>
using std::vector;

class Rule {


private:
    Predicate headPredicate;
    vector<Predicate> predList;

    vector<Rule> ruleList;


public:

  Rule () {

  }

   void AddToBody(Predicate pred) {

      predList.push_back(pred);
  }

  vector<Parameter*> GetHeadPredParams () {
      return headPredicate.GetHeaderNames();
  }

  string getHeadPredName() {
      return headPredicate.GetId();
  }


  void SetHead(Predicate headPred) {
      headPredicate = headPred;
  }

  void AddToRuleList(Rule nextRule) {
      ruleList.push_back(nextRule);
  }

  vector<Predicate> GetBodyPredicates() {
      return predList;
  }


  std::string ToString() {
      std::stringstream os;

      os << headPredicate.ToString() << " :- ";
      for(unsigned int i = 0; i < predList.size(); ++i) {
          if(i == predList.size() - 1) {
              os << predList.at(i).ToString();
              break;
          }
          os << predList.at(i).ToString() << ",";
      }

      return os.str();
  }












};

#endif //INC_236LAB2_RULES_H
