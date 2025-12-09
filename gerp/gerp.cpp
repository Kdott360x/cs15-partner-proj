/*
 *  Gerp.cpp
 *  Henry Dotterer and Tvisha Gupta
 *
 *  CS 15 PROJ4
 *
 *  purpose: Implementation of the Gerp class: builds the index and runs
 *           the interactive query loop for the gerp program.
 */

#include "gerp.h"
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

    if (not out.is_open()) {
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
        if (not in.is_open()) {
            cerr << "Warning: could not open file " 
            << filePaths[fileID] << endl;
            continue;
        }

        string line;
        int lineNum = 0;

        // read each line
        while (getline(in, line)) {
            lineNum++;
            allLines[fileID].push_back(line);

            istringstream iss(line);
            string token;

            // go through each word
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

                // create location and insert into index
                Location loc;
                loc.fileID = fileID;
                loc.lineNum = lineNum;
                loc.originalWord = token;

                //insert
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
    string stripped = stripNonAlphaNum(query);
    set<string> seen;

    // if empty query after stripping
    if (stripped.length() == 0) {
        out << " Not Found." << endl;
        return;
    }

    //lowercase everything for insensitive search purposes
    for (int i = 0; i < stripped.length(); i++) {
        stripped[i] = tolower(stripped[i]);
    }

    vector<Location> *vals = index.lookup(stripped);

    //if word isn't in the vector
    if (vals == nullptr or vals->size() == 0) {
        out << query << " Not Found." << endl;
        return;
    }

    for (int i = 0; i < vals->size(); i++) {
        Location temp = (*vals)[i];
        string output = filePaths[temp.fileID] + ":" + 
        to_string(temp.lineNum);
        if (seen.find(output) != seen.end()) {
            continue;
        }

        seen.insert(output);

        //printing logic
        out << filePaths[temp.fileID] << ":" << temp.lineNum <<
            ": " << allLines[temp.fileID][temp.lineNum - 1] << endl;
    }
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
    string stripped = stripNonAlphaNum(query);
    bool printed = false;

    //same check for empty stripped query
    if (stripped.length() == 0) {
        out << query << " Not Found. Try with @insensitive or @i." << endl;
        return;
    }

    //lowercase temporarily to get the relevant bucket
    string temp = stripped;
    for (int i = 0; i < temp.length(); i++) {
        temp[i] = tolower(temp[i]);
    }

    vector<Location> *vals = index.lookup(temp);
    if (vals == nullptr or vals->size() == 0) {
        out << query << " Not Found. Try with @insensitive or @i." << endl;
        return;
    }

    set<string> seen;

    //logic for matching original word to query now that we have bucket
    //& instances. also ensure that we only get each word once!
    for (int i = 0; i < vals->size(); i++) {
        Location loc = (*vals)[i];
        string original = stripNonAlphaNum(loc.originalWord);
        if (original != stripped) {
            continue;
        }

        
        string output = filePaths[loc.fileID] + ":" + 
                                to_string(loc.lineNum);
        if (seen.find(output) != seen.end()) {
            continue;
        }

        seen.insert(output);

        //printing logic
        out << filePaths[loc.fileID] << ":" << loc.lineNum <<
            ": " << allLines[loc.fileID][loc.lineNum - 1] << endl;

        printed = true;
    }

    //no exact match -> print not found check insensitive
    if (not printed) {
        out << query << " Not Found. Try with @insensitive or @i." << endl;
    }
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
    string line;

    while (true) {
        cout << "Query? ";

        if (not getline(cin, line)) {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return;
        }

        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        string first;
        if (not (iss >> first)) {
            continue;
        }

        // quit commands
        if (first == "@q" or first == "@quit") {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return;
        }

        // change output file
        if (first == "@f") {
            string newFile;
            if (iss >> newFile) {
                openOutput(newFile);
            }
            continue;
        }

        // case-insensitive search
        if (first == "@i" or first == "@insensitive") {
            string word;
            while (iss >> word) {
                handleInsensitiveQuery(word);
            }
            continue;
        }

        // default to case sensitive
        handleSensitiveQuery(first);

        string word;
        while (iss >> word) {
            handleSensitiveQuery(word);
        }
    }
}
