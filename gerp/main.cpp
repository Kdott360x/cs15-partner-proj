/*
 *  main.cpp
 *  Henry Dotterer and Tvisha Gupta
 *
 *  CS 15 PROJ4
 *
 *  purpose: Entry point for gerp program, sets up Gerp and runs it.
 */

#include "gerp.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/*
* name:      main
* purpose:   runs the entire gerp query function!
* arguments: command-line args from user terminal
* returns:   automatic 1
* effects:   creates a gerp object and runs the query if given
*             enough command-line arguments
* tested:    no
*/
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }
    
    try {
        Gerp g(argv[1], argv[2]);
        g.run();
    } catch (const runtime_error &e) {
        cerr << "Could not build index, reason:" << endl;
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
