/*
 *  unit_tests.h
 *  Tvisha Gupta
 *  10/30/25
 *
 *  CS 15 Proj 3: Zap
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

using namespace std;

void test1() {
   assert(stripNonAlphaNum("comp") == "comp");
   assert(stripNonAlphaNum("COMP15") == "COMP15");
   assert(stripNonAlphaNum("comp15") == "comp15");
   assert(stripNonAlphaNum("@comp") == "comp");
   assert(stripNonAlphaNum("###abc") == "abc");
   assert(stripNonAlphaNum("&&&hello") == "hello");
   assert(stripNonAlphaNum("comp!") == "comp");
   assert(stripNonAlphaNum("name???") == "name");
   assert(stripNonAlphaNum("abc***") == "abc");
   assert(stripNonAlphaNum("@@comp!!") == "comp");
   assert(stripNonAlphaNum("$$$test%%%") == "test");
   assert(stripNonAlphaNum("**hello**") == "hello");
   assert(stripNonAlphaNum("comp&!$15") == "comp&!$15");
   assert(stripNonAlphaNum("hel_lo") == "hel_lo");
   assert(stripNonAlphaNum("A-B-C") == "A-B-C");
   assert(stripNonAlphaNum("123&456") == "123&456");
   assert(stripNonAlphaNum("") == "");
   assert(stripNonAlphaNum("!!!") == "");
    assert(stripNonAlphaNum("%%%") == "");
    assert(stripNonAlphaNum("   ") == "");
    assert(stripNonAlphaNum("@#$^&*") == "");

}