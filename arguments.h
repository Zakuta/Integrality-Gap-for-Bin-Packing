#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>

#define TRUE 1
#define FALSE 0

using namespace std;

typedef struct OPTIONS {
    unsigned quiet;                        //-q option: no console output
    unsigned loud;                        //-v option: enables Gurobi output
    unsigned random;                    //-r option: generation of a random bin packing instance.'
    unsigned nodefiles;                 //-b enable use of Gurobi nodefiles to solve the IP.
    string inFile;                        //-f <inFile>: Read instance from file <inFile>.
    unsigned succeededToReadArguments;    //If unknown arguments are given or non-optional names are not specified, if anything fails, this will be set to false
    OPTIONS() :
            quiet(FALSE), loud(FALSE),
            inFile(), random(FALSE), nodefiles(FALSE),
            succeededToReadArguments(TRUE) {}
} OPTIONS;

OPTIONS parseargs(int argc, char *argv[]);


#endif //BP_EA_COURSE_ARGUMENTS_H
