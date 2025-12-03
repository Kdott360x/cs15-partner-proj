/*
 *  processing.h
 *  Henry Dotterer and Tvisha Gupta 
 *  11/18/25
 *
 *  CS 15 PROJ4
 *
 *  purpose: This file contains the interface for the processing.cpp functions.
 */


#ifndef __PROCESSING_H
#define __PROCESSING_H

#include <string>
using namespace std;

string stripNonAlphaNum(string input);
void traverseDirectory(string directory);
void collectFiles(const std::string &rootDir,
                  std::vector<std::string> &files);

#endif 