#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "helper.h"

/*
 * Solution<T> is a class used to save and output linear and integral solutions
 * of a bin packing problem.
 */

using namespace std;

template <typename T>
class Solution {
private:
    T opt;                                                                        //optimal objective function value.
    vector <T> coefficients;                                                    //coefficients of the patterns
    vector <vector <unsigned> > pattern;                                        //all patterns with coefficient > 0
    unsigned size;                                                                //size of coefficient vector

public:
    Solution();
    Solution(unsigned n);                                                        //resizes coefficients to size n and pattern to size n (the vectors inside are
                                                                                //not resized after this function), sets size = n.

    T getOpt();
    T getCoefficient(unsigned i);
    vector<unsigned> getPattern(unsigned i);
    unsigned getSize();

    void setOpt(T value);
    void setCoeff(unsigned i, double x);
    void setPattern(unsigned i,vector<unsigned> p);
    void setPatternat(unsigned i, unsigned j, unsigned p);
    void resizePattern(unsigned i, unsigned n);
    void resizeAll(unsigned k);                                                    //resizes coefficients and pattern, sets size.

    void saveSolution(GRBModel * model, const std::vector<double> &sizeVector, unsigned kind);        //extracts solution from model. The type of LP/IP has to be determined by
                                                                                //parameter kind: kind == 0: model describes full Gilmore-Gomory LP or LP
                                                                                //created by column generation.
                                                                                //kind == 1: model describes Gilmore-Gomory IP.
                                                                                //kind == 2: model describes modified Kantorovich IP.

};
#define SOLUTION_FUNCTIONS
#include "solution.cpp"
#endif // SOLUTION_H
