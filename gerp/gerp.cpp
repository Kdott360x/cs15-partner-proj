/*
 *  Gerp.cpp
 *  Henry Dotterer and Tvisha Gupta
 *
 *  CS 15 PROJ4
 *
 *  purpose: Implementation of the Gerp class: builds the index and runs
 *           the interactive query loop for the gerp program.
 */

#include "Gerp.h"
#include "processing.h"
#include <sstream>
#include <cctype>
#include <iostream>
#include <set>

using namespace std;

/*
* name:      Gerp
* purpose:   constructor, builds the word index and opens the output file
* arguments: rootDir    - directory to index
*            outputFile - initial output file name
* returns:   none
* effects:   builds index and opens output file stream
* tested:    no
*/
Gerp::Gerp(const string &rootDir, const string &outputFile) {
    openOutput(outputFile);
    buildIndex(rootDir);
}

/*
* name:      ~Gerp
* purpose:   destructor, closes output file if open
* arguments: none
* returns:   none
* effects:   closes ofstream
* tested:    no
*/
Gerp::~Gerp() {
    if (out.is_open()) {
        out.close();
    }
}

/*
* name:      openOutput
* purpose:   open a new output file (closing any existing one)
* arguments: filename - name of file to open for output
* returns:   none
* effects:   closes previous ofstream and opens a new one
* tested:    no
*/
void Gerp::openOutput(const string &filename) {
    if (out.is_open()) {
        out.close();
    }
    out.open(filename);

    if (!out.is_open()) {
        cerr << "Error: could not open output file " << filename << endl;
    }
}

/*
* name:      buildIndex
* purpose:   build the hash table index over all files in a directory
* arguments: rootDir - directory to traverse and index
* returns:   none
* effects:   fills index, filePaths, and allLines
* tested:    no
*/
void Gerp::buildIndex(const string &rootDir) {
    // collect all file paths under rootDir
    collectFiles(rootDir, filePaths);
    allLines.resize(filePaths.size());

    // read each file line by line and insert words into the hash table
    for (int fileID = 0; fileID < (int) filePaths.size(); fileID++) {
        ifstream in(filePaths[fileID]);
        if (!in.is_open()) {
            cerr << "Warning: could not open file " 
            << filePaths[fileID] << endl;
            continue;
        }

        string line;
        int lineNum = 0;

        while (getline(in, line)) {
            lineNum++;
            allLines[fileID].push_back(line);

            istringstream iss(line);
            string token;

            while (iss >> token) {
                string stripped = stripNonAlphaNum(token);
                if (stripped.empty()) {
                    continue;
                }

                // lowercase key for index
                string key = stripped;
                for (char &c : key) {
                    c = tolower(c);
                }

                Location loc;
                loc.fileID = fileID;
                loc.lineNum = lineNum;
                loc.originalWord = token;

                index.insert(key, loc);
            }
        }
    }
}

/*
* name:      handleInsensitiveQuery
* purpose:   process a case-insensitive query and write results to output file
* arguments: query - query word typed by the user
* returns:   none
* effects:   writes matching lines (at most once per line) to out
* tested:    no
*/
void Gerp::handleInsensitiveQuery(const string &query) {
}

/*
* name:      handleSensitiveQuery
* purpose:   process a case-sensitive query and write results to output file
* arguments: query - query word typed by the user
* returns:   none
* effects:   writes matching lines to out
* tested:    no
*/
void Gerp::handleSensitiveQuery(const string &query) {
}

/*
* name:      run
* purpose:   run the interactive query loop
* arguments: none
* returns:   none
* effects:   reads commands from cin, writes results to current output file
* tested:    no
*/
void Gerp::run() {

}
