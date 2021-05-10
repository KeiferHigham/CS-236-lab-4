#ifndef INC_236LAB3_TUPLE_H
#define INC_236LAB3_TUPLE_H
#include <vector>
#include <string>

using std::string;
using std::vector;


class Tuple {


private:

    vector<string> values;





public:

    Tuple() {

    }

    void addToTuple(string value) {
        values.push_back(value);
    }

    bool operator< (const Tuple& other) const {
        return this->values < other.GetValues();
    }

    vector<string> GetValues() const {
        return values;
    }







    // make sure to implement the < operator here for comapring tuples

};

#endif //INC_236LAB3_TUPLE_H
