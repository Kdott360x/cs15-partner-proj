/*
 *  processing.cpp
 *  Henry Dotterer and Tvisha Gupta 
 *  11/18/25
 *
 *  CS 15 PROJ3
 *
 *  purpose: This program compresses and decompresses files using Huffman coding
 */

#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <string>
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
    // check if valid first char
    if (isalnum(input[0])) {
        // all set
    } else {
        int chars_to_remove = 0;
        int index = 0;

        // count non-alphanumeric chars at start
        while (not isalnum(input[index])) {
            chars_to_remove++;
            index++;
        }

        // remove them
        input = input.substr(chars_to_remove, input.length());
    }

    // count backwards
    if (isalnum(input[input.length() - 1])) {
        // all set
    } else {
        int chars_to_remove = 0;
        int index = input.length() - 1;

        // count non-alphanumeric chars from end, work backward
        while (not isalnum(input[index])) {
            chars_to_remove++;
            index--;
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

