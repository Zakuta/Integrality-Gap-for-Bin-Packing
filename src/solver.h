#ifndef SOLVER_H
#define SOLVER_H

#include "solution.h"
#include "gurobi_c++.h"

/* Solver is an abstract class that serves as an interface for different
 * solvers.
 *
 * typename T is the solution type (so double for LP, unsigned for IP).
 * inst is a pointer to an already generated bin packing instance.
 * model is a pointer to an already allocated GRBModel.
 * sol is a reference to a Solution object, there the solution will be written.
 * env is a pointer to an already allocated GRBEnv. This is only necessary
 *        for colgenSolver and modifiedKantorovichIPSolver, since these will
 *        generate a new model.
 * Returned is a pointer to a model which should be assigned to the given model
 *
 * Depending on the chosen solver some things have to be computed and set
 * before a call to buildAndSolve. For this see the specific solvers.
 */

template <typename T>
class Solver {
public:
    virtual ~Solver(){}
    virtual GRBModel * buildAndSolve(const std::vector<double> &sizeVector, GRBModel * model, Solution<T>& sol, GRBEnv * env) = 0;
};

#endif // SOLVER_H
