#ifndef INC_236LAB3_HEADER_H
#define INC_236LAB3_HEADER_H
#include <string>
#include <vector>

using std::vector;
using std::string;

class Header {



private:

 vector<string> attributes;


public:

    Header() {

    }

    void AddHeader(string headerName)  {
        string name = headerName;
        attributes.push_back(name);
    }


    vector<string> GetAttributeNames() {
        return attributes;
    }


    void UpdateNames(vector<string> newHeaderNames) {

        for(unsigned int i = 0; i < attributes.size(); ++i) {

            attributes.at(i) = newHeaderNames.at(i);
        }

    }



};
#endif //INC_236LAB3_HEADER_H
