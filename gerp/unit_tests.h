/*
 *  unit_tests.h
 *  Henry Dotterer
 *  12/4/25
 *
 *  CS 15 Proj 4: Gerp
 *
 *  The interface for the unit tests!
 *
 */

#include <cassert>
#include <sstream>
#include <string>
#include <iostream>
#include "processing.h"
#include "DirNode.h"
#include "FSTree.h"
#include "hashTable.h"

using namespace std;

//tests the stripAlpha function
void strip_test() {
   assert(stripNonAlphaNum("test123") == "test123");
   assert(stripNonAlphaNum("TEST123") == "TEST123");
   assert(stripNonAlphaNum("test") == "test");
   assert(stripNonAlphaNum("$test") == "test");
   assert(stripNonAlphaNum("@@@test") == "test");
   assert(stripNonAlphaNum("hello!") == "hello");
   assert(stripNonAlphaNum("@@test!!") == "test");
   assert(stripNonAlphaNum("@@@test$$$") == "test");
   assert(stripNonAlphaNum("**test**") == "test");
   assert(stripNonAlphaNum("comp&!$15") == "comp&!$15");
   assert(stripNonAlphaNum("te_st") == "te_st");
   assert(stripNonAlphaNum("abcd&def") == "abcd&def");
   assert(stripNonAlphaNum("") == "");
   assert(stripNonAlphaNum("   ") == "");
   assert(stripNonAlphaNum("@#$^&*") == "");
}

//tests for the hashTable functions and class bulding
void hash_test1() {
   hashTable test;
   vector<Location> *result = test.lookup("hello");
   assert(result == nullptr);
}

void hash_test2() {
   hashTable test;
   Location temp;
   temp.fileID = 1;
   temp.lineNum = 1;
   temp.originalWord = "hello";
   test.insert("hello", temp);
   vector<Location> *result = test.lookup("hello");
   Location &ans = (*result)[0];
   assert(test.size() == 1);
   assert(result->size() == 1);
   assert(ans.fileID == 1);
   assert(ans.lineNum == 1);
   assert(ans.originalWord == "hello");
}

void hash_test3() {
   hashTable test;
   Location temp1, temp2, temp3;
   temp1.fileID = 0;
   temp1.lineNum = 1;
   temp1.originalWord = "hello";
   temp2.fileID = 0;
   temp2.lineNum = 2;
   temp2.originalWord = "hello";
   temp3.fileID = 0;
   temp3.lineNum = 3;
   temp3.originalWord = "hello";
   test.insert("hello", temp1);
   test.insert("hello", temp2);
   test.insert("hello", temp3);
   vector<Location> *result = test.lookup("hello");
   assert(result->size() == 3);
   for(int i = 0; i < result->size(); i++) {
      Location &ans = (*result)[i];
      assert(ans.fileID == 0);
      assert(ans.lineNum >= 1 and ans.lineNum <= 3);
      assert(ans.originalWord == "hello");
   }
}

void hash_test4() {
   hashTable test;
   Location temp1, temp2;
   temp1.fileID = 0;
   temp1.lineNum = 1;
   temp1.originalWord = "hello";
   temp2.fileID = 1;
   temp2.lineNum = 2;
   temp2.originalWord = "gerpprog";
   test.insert("hello", temp1);
   test.insert("gerpprog", temp2);
   vector<Location> *result1 = test.lookup("hello");
   Location &ans1 = (*result1)[0];
   assert(ans1.fileID == 0);
   assert(ans1.lineNum == 1);
   assert(ans1.originalWord == "hello");
   vector<Location> *result2 = test.lookup("gerpprog");
   Location &ans2 = (*result2)[0];
   assert(ans2.fileID == 1);
   assert(ans2.lineNum == 2);
   assert(ans2.originalWord == "gerpprog");
}