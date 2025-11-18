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


string stripNonAlphaNum(string input){
    
}



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


void traverseDirectory(string directory){
    // build the file-system with root "directory"
    FSTree tree(directory);
    DirNode *root = tree.getRoot();

    // start recursion with empty path to prevent duplicates
    traverseDirectoryHelper(root, "");
}

