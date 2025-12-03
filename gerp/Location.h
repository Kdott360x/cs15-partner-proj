#ifndef LOCATION_H
#define LOCATION_H

#include <string>

struct Location {
    int fileID;
    int lineNum;
    std::string originalWord;
};

#endif
