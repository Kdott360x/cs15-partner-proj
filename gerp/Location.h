#ifndef LOCATION_H
#define LOCATION_H

#include <string>

struct Location {
    int fileID;
    int lineNum;
    std::string originalWord;
    std::string *originalLine;   // keep this for now since your hashTable uses it
};

#endif
