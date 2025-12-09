/*
 *  Location.h
 *  Henry Dotterer and Tvisha Gupta 
 *  11/23/25
 *
 *  CS 15 PROJ4
 *
 *  purpose: Creates the publically accessible Location struct used to
 *           store the fileID, lineNum, and originalWord for each word
 *           instance in the hash table. Also no implementation .cpp file needed
 */
#ifndef LOCATION_H
#define LOCATION_H

#include <string>

struct Location {
    int fileID;
    int lineNum;
    std::string originalWord;
};

#endif
