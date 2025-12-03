/*
 *  processing.cpp
 *  Henry Dotterer and Tvisha Gupta 
 *  11/18/25
 *
 *  CS 15 PROJ4
 *
 *  purpose: This file contains the implementations for the 
 *  directory traversal and stripping nonalphanumeric characters functions.
 */

#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
* name:      stripNonAlphaNum
* purpose:   remove leading and trailing non-alphanum chars from string
* arguments: input - string (possibly with non-alphanum chars at ends)
* returns:   string with all leading/trailing non-alphanum chars removed
* effects:   none
* tested:    no
*/
string stripNonAlphaNum(string input){
    //checks if empty string
    if(input.length() == 0) {
        return input;
    }

    // check if valid first char
    if (not isalnum(input[0])) {
        int chars_to_remove = 0;
        size_t index = 0;

        // count non-alphanumeric chars at start
        while (index < input.length() and (not isalnum(input[index]))) {
            chars_to_remove++;
            index++;
        }

        //no alphanumeric characters
        if (index == input.length()) {
            return "";
        }

        // remove them
        input = input.substr(chars_to_remove, input.length());
    }

    // count backwards
    if (not isalnum(input[input.length() - 1])) {
        int chars_to_remove = 0;
        int index = input.length() - 1;

        // count non-alphanumeric chars from end, work backward
        while (index >= 0 and (not isalnum(input[index]))) {
            chars_to_remove++;
            index--;
        }

        //no alphanumeric characters
        if (index < 0) {
            return "";
        }

        // remove
        input = input.substr(0, input.length() - chars_to_remove);
    }

    return input;
}


/*
* name:      traverseDirectoryHelper
* purpose:   recursively traverse a directory tree and print all paths for file
* arguments: node      - pointer to the current DirNode
*            pathSoFar - path prefix accumulated so far
* returns:   none
* effects:   writes one line to cout for each file in the subtree rooted at node
* tested:    no 
*/
static void traverseDirectoryHelper(DirNode *node, string pathSoFar) {
    if (node == nullptr) {
        return;
    }

    // print connection
    pathSoFar += node->getName() + "/";

    // print files
    for (int i = 0; i < node->numFiles(); i++) {
        cout << pathSoFar << node->getFile(i) << endl;
    }

    // recurse subdirs 
    for (int j = 0; j < node->numSubDirs(); j++) {
        DirNode *subdir = node->getSubDir(j);
        traverseDirectoryHelper(subdir, pathSoFar);
    }
}

/*
* name:      traverseDirectory
* purpose:   build an FSTree for the directory and print paths for all files
* arguments: directory - name/path of the root directory to traverse
* returns:   none
* effects:   constructs an FSTree and writes one line to cout for each file
* tested:    no
*/
void traverseDirectory(string directory){
    // build the file-system with root "directory"
    FSTree tree(directory);
    DirNode *root = tree.getRoot();

    // start recursion with empty path to prevent duplicates
    traverseDirectoryHelper(root, "");
}

// NEW helper: collect all file paths into a vector instead of printing
static void collectFilesHelper(DirNode *node,
                               string pathSoFar,
                               vector<string> &files) {
    if (node == nullptr) {
        return;
    }

    pathSoFar += node->getName() + "/";

    // add files in this directory
    for (int i = 0; i < node->numFiles(); i++) {
        files.push_back(pathSoFar + node->getFile(i));
    }

    // recurse into subdirectories
    for (int j = 0; j < node->numSubDirs(); j++) {
        DirNode *subdir = node->getSubDir(j);
        collectFilesHelper(subdir, pathSoFar, files);
    }
}

// NEW top-level function: wrapper that builds the FSTree and calls helper
void collectFiles(const string &rootDir, vector<string> &files) {
    FSTree tree(rootDir);
    DirNode *root = tree.getRoot();
    collectFilesHelper(root, "");
}