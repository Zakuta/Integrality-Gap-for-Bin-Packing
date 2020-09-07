#include "bpinstance.h"
#include <sys/time.h>
#include "solution.h"
#include <algorithm>
#include <random>
#include <chrono>
#include "helper.h"
#include <fstream>

BPInstance::BPInstance() {
}

BPInstance::BPInstance(string inFilename)
{
    ifstream inFile;
    inFile.open(inFilename.c_str(),ios::in);
    string check;
    if( !inFile.is_open() ) {
        cout << "Error: Input-file " <<inFilename<< " could not be opened.\n";
        return;
    }

    inFile >> check >> nrOfItems;
    if(inFile.fail() || check != "n") {
        cout << "Error: Input-file " <<inFilename<< " does not have required format.\n";
        inFile.close();
        return;
    }
    resNrOfItems = nrOfItems;
    mult.resize(nrOfItems);
    sizes.resize(nrOfItems);
    for (unsigned i = 0; i < nrOfItems; i++) {
        inFile >> check >> sizes[i];
        if(inFile.fail() || check != "s") {
            cout << "Error: Input-file " <<inFilename<< " does not have required format.\n";
            inFile.close();
            return;
        }
    }
    for (unsigned i = 0; i < nrOfItems; i++) {
        inFile >> check >> mult[i];
        if(inFile.fail() || check != "m") {
            cout << "Error: Input-file " <<inFilename<< " does not have required format.\n";
            inFile.close();
            return;
        }
    }
    inFile.close();
}

bool BPInstance::printToStream(ostream & output) {
    output << "n " << resNrOfItems << endl;
    for(unsigned i = 0; i < nrOfItems; i++) {
        if(mult[i] > 0) output << "s " << sizes[i] << endl;
    }
    for(unsigned i = 0; i < nrOfItems; i++) {
        if(mult[i] > 0) output << "m " << mult[i] << endl;
    }
    if(!output.good()) return false;
    else return true;
}

