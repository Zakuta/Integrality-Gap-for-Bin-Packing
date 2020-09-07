#ifndef BPINSTANCE_H
#define BPINSTANCE_H

#include "gurobi_c++.h"
#include <string>
#include <iostream>

using namespace std;

template<typename T>
class Solution;

class BPInstance {

private:
    unsigned nrOfItems;                                                            //Number of item sizes = length of vectors
    unsigned resNrOfItems;                                                        //Number of item sizes after computing the residual instance. In general not
                                                                                //the size of the vectors.
    vector<int> mult;                                                            //mult[i] = number of times item i has to be packed.
    vector<double> sizes;                                                        //sizes[i] = size of item i.

public:
    BPInstance();                                                                //Default Constructor: Never used.

    BPInstance(string inFilename);                                                //Constructor that reads the instance from inFilename. For necessary format
                                                                                //see bpinstance.cpp
    unsigned getNrOfItems(){return nrOfItems;}
    int getMult(unsigned i) {return mult[i];}
    double getSize(unsigned i) {return sizes[i];}

    void setMult(unsigned i, unsigned newMult) {mult[i] = newMult;}

    bool printToStream(ostream & output);                                        //Outputs the instance to the ostream output.
};

#endif // BPINSTANCE_H
