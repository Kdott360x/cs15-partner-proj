/*
 *  hashTable.cpp
 *  Henry Dotterer and Tvisha Gupta 
 *  11/23/25
 *
 *  CS 15 PROJ4
 *
 *  purpose: This file contains the implementations for the 
 *  directory traversal and stripping nonalphanumeric characters functions.
 */

#include "FSTree.h"
#include "DirNode.h"
#include "hashTable.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
* name:      hashTable
* purpose:   the constructor for this class, initializes all basic vars
* arguments: none
* returns:   none
* effects:   gives default vals for all member variables
*/
hashTable::hashTable() {
    buckets.resize(201);
    numElements = 0;
    loadFactor = 0.7;
}

/*
* name:      insert()
* purpose:   inserts a word and its loc in the correct bucket in the hash table
* arguments: the key string and the Location value
* returns:   none
* effects:   updates vector buckets
*/
void hashTable::insert(const string &key, Location &value) {
    bool temp = false;
    
    //calculate where elem should be & get address in vector
    int bucketNum = hasher(key, -1);
    vector<Element> &currBucket = buckets[bucketNum];

    //look for key in vector in current bucket
    for(int i = 0; i < currBucket.size(); i++) {
        if (currBucket[i].key == key) {
            currBucket[i].locs.push_back(value);
            temp = true;
        }
    }

    //add new key-val pair to vector if not there
    if (temp == false) {
        Element elem;
        elem.key = key;
        elem.locs.push_back(value);
        currBucket.push_back(elem);
        numElements++;
    }

    //calculate curr load factor & rehash if needed
    float currLoad = (float) numElements/ (float) buckets.size();
    if (currLoad > loadFactor) {
        rehash();
    }
}

/*
* name:      lookup()
* purpose:   finds the correct Location vector for a particular key
* arguments: the key string 
* returns:   pointer to the Locations vector if it exists
* effects:   none
*/
vector<Location>* hashTable::lookup(const string &key) {
    //calculate which bucket we should be looking through
    int bucketNum = hasher(key, -1);
    vector<Element> &currBucket = buckets[bucketNum];

    //return the whole appropriate vector
    for(int i = 0; i < currBucket.size(); i++) {
        if (currBucket[i].key == key) {
            return &currBucket[i].locs;
        }
    }
    
    return nullptr;
}

/*
* name:      size()
* purpose:   returns number of elemnts of the table
* arguments: none
* returns:   the count of keys
* effects:   none
*/
int hashTable::size() {
    return numElements;
}

/*
* name:      hasher()
* purpose:   calculates the correct bucket for a particular key
* arguments: the key string and an int to indicate what to mod by (case basis)
* returns:   bucket index
* effects:   none
*/
int hashTable::hasher(const string &key, int mod) {
    hash<string> hashObj;
    size_t hashNum = hashObj(key);
    int divisor;
    if(mod == -1) {
        divisor = buckets.size();
    } else {
        divisor = mod; 
    }
    int bucket = hashNum % divisor;
    return bucket;
}

/*
* name:      rehash()
* purpose:   expands table and reinserts elements
* arguments: none
* returns:   none
* effects:   creates a new, expanded hash table
*/
void hashTable::rehash() {
    int oldSize = buckets.size();
    int currSize = (oldSize*2) + 1;
    vector<vector<Element>> currBuckets;
    currBuckets.resize(currSize);

    for (int i = 0; i < oldSize; i++) {
        vector<Element> &old = buckets[i];
        for (int j = 0; j < old.size(); j++) {
            Element elem = old[j];
            int index = hasher(elem.key, currSize);
            currBuckets[index].push_back(elem);
        }
    }
    
    buckets = currBuckets;
}
