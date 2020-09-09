#ifndef HELPER_H
#define HELPER_H

#include "gurobi_c++.h"
#include <string>
#include <sstream>
#include <limits>
#include <cmath>

/*
 * This file declares a few very useful helper functions, mainly to handle
 * comparisons between double and unsigned values.
 *
 * It also contains a function to set the needed parameters for a GRBEnv.
 */

using namespace std;

bool isLargerEqualZero(double number, int multiplicator);                       //checks if number >= -multiplicator*numeric_limits<double>::epsilon()
bool isZero(double number, int multiplicator);                                  //checks if number \in (-multiplicator*epsilon(),-multiplicator*epsilon())

template <typename T>
string NumberToString ( T Number )
{
    stringstream ss;
    ss << Number;
    return ss.str();
}

template<typename T>
string VectorToString(vector<T> input)
{
    stringstream ss;
    ss << "[";
    for(int i = 0; i < input.size()-1; i++) {
        ss << input[i] << ", ";
    }
    ss << input[input.size()-1] << "]";
    return ss.str();
}

string printDouble(double number);                                              //
int almostIntToInt(double x);                                                   //

void setEnvParams(GRBEnv * env, unsigned loud, unsigned memory);

#endif // HELPER_H
