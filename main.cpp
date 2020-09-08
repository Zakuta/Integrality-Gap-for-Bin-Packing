#include "simpleipsolver.h"
#include "simplelpsolver.h"
#include <string>

#define TRUE 1
#define FALSE 0

int main()
{
    unsigned loud = FALSE;                        // option: enables Gurobi output
    unsigned nodeFiles = FALSE;                 // enable use of Gurobi nodefiles to solve the IP.

    string inFile;
    cout << "Path to the input file: ";
    cin >> inFile;
    BPInstance *inst;

    inst = new BPInstance(inFile);


    Solver<double> *solverLP;
    solverLP = new SimpleLPSolver();

    Solution<double> solLP(inst->getNrOfItems());

    GRBEnv *env = new GRBEnv();
    setEnvParams(env, loud, nodeFiles);
    GRBModel *model = new GRBModel(*env);
    model = solverLP->buildAndSolve(inst,model,solLP, env);

    if(model == NULL) {
        cout << "LP Model is NULL!" << endl;
        return 1;
    }

    Solver<unsigned> *solverIP;
    Solution<unsigned> solIP;

    solverIP = new SimpleIPSolver();

    model = solverIP->buildAndSolve(inst,model,solIP, env);

    if(model == NULL) {
        cout << "IP Model is NULL!" << endl;
        return 1;
    }

    double gap;

    gap = solIP.getOpt()-solLP.getOpt();

    cout << "GAP " << printDouble(gap) << endl;

//    Free Memory
    delete solverIP;
    delete solverLP;
    delete inst;
    delete model;
    delete env;
    return 0;
}
