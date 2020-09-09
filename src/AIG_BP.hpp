
#ifndef _F_AIG_BP_HPP
#define _F_AIG_BP_HPP

#include "simpleipsolver.h"
#include "simplelpsolver.h"
#include <string>

#define TRUE 1
#define FALSE 0



#include "IOHprofiler_problem.h"

class AIG_BP : public IOHprofiler_problem<double> {
public:
  AIG_BP(int instance_id = DEFAULT_INSTANCE, int dimension = DEFAULT_DIMENSION) {

    IOHprofiler_set_instance_id(instance_id);
    IOHprofiler_set_problem_name("AIG_BP");
    IOHprofiler_set_problem_type("continuous");
    IOHprofiler_set_number_of_objectives(1);
    IOHprofiler_set_lowerbound(0);
    IOHprofiler_set_upperbound(50);
    IOHprofiler_set_number_of_variables(dimension);
  }
  
  ~AIG_BP() {}


  double internal_evaluate(const std::vector<double> &sizeVector) {
    unsigned loud = FALSE;                        // option: enables Gurobi output
    unsigned nodeFiles = FALSE;                 // enable use of Gurobi nodefiles to solve the IP.
    unsigned nrOfItems = sizeVector.size();
    std::vector<double> result(1);

    for (unsigned i = 0; i < nrOfItems; i++) {
        if ((sizeVector[i]<=0) && (sizeVector[i]>=1)) {
            cout << "The size vector of the bin packing instance is invalid.\n";
        }
    }

    Solver<double> *solverLP;
    solverLP = new SimpleLPSolver();

    Solution<double> solLP(nrOfItems);

    GRBEnv *env = new GRBEnv();
    setEnvParams(env, loud, nodeFiles);
    GRBModel *model = new GRBModel(*env);
    model = solverLP->buildAndSolve(sizeVector, model, solLP, env);

    if(model == nullptr) {
        cout << "LP Model is NULL!" << endl;
        return 1;
    }

    Solver<unsigned> *solverIP;
    Solution<unsigned> solIP;

    solverIP = new SimpleIPSolver();

    model = solverIP->buildAndSolve(sizeVector, model,solIP, env);

    if(model == nullptr) {
        cout << "IP Model is NULL!" << endl;
        return 1;
    }

    result[0] = solIP.getOpt()-solLP.getOpt();

//    cout << "GAP " << printDouble(result[0]) << endl;

//    Free Memory
    delete solverIP;
    delete solverLP;
    delete model;
    delete env;
    return result[0];
  }

  static AIG_BP * createInstance(int instance_id = DEFAULT_INSTANCE, int dimension = DEFAULT_DIMENSION) {
    return new AIG_BP(instance_id, dimension);
  }
};

#endif