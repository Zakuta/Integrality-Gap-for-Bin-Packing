#ifndef SIMPLELPSOLVER_H
#define SIMPLELPSOLVER_H

#include "solver.h"

/*
 * SimpleLPSolver is used when building the whole Gilmore-Gomory LP.
 */

class SimpleLPSolver : public Solver<double>
{
public:
    SimpleLPSolver(){}
    GRBModel * buildAndSolve(const std::vector<double> &sizeVector, GRBModel * model,                //Builds the Gilmore-Gomory LP for the instance inst. model has to be allocated
                             Solution<double>& sol, GRBEnv * env);                //as well as env. After optimization solution is saved in sol.

private:
    void tryNewItem(const std::vector<double> &sizeVector, GRBModel * model, vector<int> & x,        //called recursively to enumerate all possible patterns. model and inst as above
                    int newItem, double restCap, GRBLinExpr *lhsConstraints,    //x is the current pattern vector, restCap is the capacity that x has right now,
                    int depth, unsigned& varNumber);                            //newItem is the number of the item we want to pack on top of x, lhsConstraints
                                                                                //is an array of linear constraints that will afterwards be the lhs in the LP,
                                                                                //depth is the number of times we subtracted a double value from restCap up till
                                                                                //now. varNumber counts the variables, we name the variables after the value of
                                                                                //varNumber when they were added to the model.
};

#endif // SIMPLELPSOLVER_H
