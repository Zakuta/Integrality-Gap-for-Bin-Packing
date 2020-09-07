#include "arguments.h"
#include <cstdio>
#include <iostream>

using namespace std;

void usage(char *prog) {
    cout << "Program call: "<< prog << " [OPTIONS]\nFull options list:\n";
    cout << "    -f <filename>  Read instance from file given and test it.\n\n";
    cout << "    -q             No console output at all.\n";
    cout << "    -v             Apart from default output, also enable Gurobi console output.\n";
}


OPTIONS parseargs(int argc, char *argv[]) {
    OPTIONS commandline;
    for (int cnt = 1; cnt < argc && argv[cnt][0] == '-'; cnt++) {
        switch (argv[cnt][1]) {
            case 'q':
                commandline.quiet = TRUE;
                commandline.loud = FALSE;
                break;
            case 'v':
                commandline.loud = TRUE;
                commandline.quiet = FALSE;
                break;
            case 'f':
                commandline.random = FALSE;
                cnt++;
                if (cnt >= argc || argv[cnt][0] == '-') {
                    commandline.random = TRUE;
                    usage(argv[0]);
                    commandline.succeededToReadArguments = FALSE;
                    break;
                }
                commandline.inFile = argv[cnt];
                break;
        }
    }
    return commandline;
}