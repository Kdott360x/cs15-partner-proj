/*
 *  hashTable.h
 *  Henry Dotterer and Tvisha Gupta 
 *  11/23/25
 *
 *  CS 15 PROJ4
 *
 *  purpose: This file contains the interface for the processing.cpp functions.
 */


#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <functional>
#include "Location.h"

using namespace std;

class hashTable {
public:
    hashTable(); //constructor
    void insert(const string &key, Location &value);
    vector<Location> *lookup(const string &key);
    int size();

private:
    struct Element {
        string key;
        vector<Location> locs;
    };

    vector<vector<Element>> buckets;
    float loadFactor;
    int numElements;
    void rehash();
    int hasher(const string &key, int mod);
};

#endif