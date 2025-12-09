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
* name:      collectFilesHelper
* purpose:   recursively traverse a directory tree and record all file paths
* arguments: node      - pointer to the current DirNode
*            pathSoFar - path prefix accumulated so far
*            files     - vector to add full file paths into
* returns:   none
* effects:   pushes one string into files for each file in the subtree
* tested:    no
*/
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

/*
* name:      collectFiles
* purpose:   build an FSTree and collect paths for all files in a directory
* arguments: rootDir - name/path of the root directory to traverse
*            files   - vector to add full file paths into
* returns:   none
* effects:   constructs an FSTree and add one string to files for each file
* tested:    no
*/
void collectFiles(const string &rootDir, vector<string> &files) {
    FSTree tree(rootDir);
    DirNode *root = tree.getRoot();
    collectFilesHelper(root, "", files);
}