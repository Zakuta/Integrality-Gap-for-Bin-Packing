#ifndef SIMPLEIPSOLVER_H
#define SIMPLEIPSOLVER_H

#include "solver.h"

/*
 * SimpleIPSolver is used for solving the Gilmore-Gomory IP.
 * It can only be used after SimpleLPSolver::buildAndSolve has been called
 * before with the same model.
 */

class SimpleIPSolver : public Solver <unsigned>
{
public:
    GRBModel * buildAndSolve(BPInstance * test, GRBModel * model,               //model has to be allocated and has to contain the Gilmore-Gomory LP.
                             Solution<unsigned> & sol, GRBEnv * env);           //The function changes each variable type to integer and optimizes again
};                                                                              //solution is saved in sol.

#endif // SIMPLEIPSOLVER_H
