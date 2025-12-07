/*
 *  hashTable.h
 *  Henry Dotterer and Tvisha Gupta 
 *  11/23/25
 *
 *  CS 15 PROJ4
 *
 *  purpose: This file contains the interface for the processing.cpp functions.
            It defines the public functions that the user can use to interact
            with the contents of the hash table, including inserting and 
            looking up words, and private variables that allow us to
            actually create the table and track whether we need to rehash.
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
    hashTable();
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