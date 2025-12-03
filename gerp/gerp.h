/*
 *  Gerp.h
 *  Henry Dotterer and Tvisha Gupta
 *
 *  CS 15 PROJ4
 *
 *  purpose: Declaration of the Gerp class, which builds the index and handles
 *           queries for the gerp program.
 */


#ifndef GERP_H
#define GERP_H

#include <string>
#include <vector>
#include <fstream>
#include "hashTable.h"
#include "Location.h"

class Gerp {
public:
    Gerp(const std::string &rootDir, const std::string &outputFile);
    ~Gerp();

    void run();

private:
    void buildIndex(const std::string &rootDir);
    void openOutput(const std::string &filename);
    void handleSensitiveQuery(const std::string &query);
    void handleInsensitiveQuery(const std::string &query);

    hashTable index;                  
    std::vector<std::string> filePaths;    
    std::vector<std::vector<std::string>> allLines;
    std::ofstream out;                         
};

#endif
