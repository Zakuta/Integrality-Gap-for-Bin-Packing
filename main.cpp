#include "simpleipsolver.h"
#include "simplelpsolver.h"
#include <string>

#define TRUE 1
#define FALSE 0

double internal_evaluate(const std::vector<double> &sizeVector)
{
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

int main() {
//    vector<double> sizeVector = {0.109375, 0.109375, 0.16145833, 0.17708333, 0.24479167, 0.25, 0.26041667, 0.34375,
//                                 0.39583333, 0.39583333, 0.5, 0.5, 0.5, 0.50520833, 0.50520833, 0.578125, 0.66145833,
//                                 0.74479167, 0.76041667};

    vector<double> sizeVector = {0.12,0.12,0.165,0.18,0.245,0.25,0.26,0.35,0.39,0.5,0.5,0.5,
    0.505,0.575,0.655,0.75,0.76};

    cout << internal_evaluate(sizeVector) << endl;
    return 0;
}

//int main()
//{
//    unsigned loud = FALSE;                        // option: enables Gurobi output
//    unsigned nodeFiles = FALSE;                 // enable use of Gurobi nodefiles to solve the IP.
//
//    string inFile;
//    cout << "Path to the input file: ";
//    cin >> inFile;
//    BPInstance *inst;
//
//    inst = new BPInstance(inFile);
//
//
//    Solver<double> *solverLP;
//    solverLP = new SimpleLPSolver();
//
//    Solution<double> solLP(inst->getNrOfItems());
//
//    GRBEnv *env = new GRBEnv();
//    setEnvParams(env, loud, nodeFiles);
//    GRBModel *model = new GRBModel(*env);
//    model = solverLP->buildAndSolve(inst, model,solLP, env);
//
//    if(model == NULL) {
//        cout << "LP Model is NULL!" << endl;
//        return 1;
//    }
//
//    Solver<unsigned> *solverIP;
//    Solution<unsigned> solIP;
//
//    solverIP = new SimpleIPSolver();
//
//    model = solverIP->buildAndSolve(inst,model,solIP, env);
//
//    if(model == NULL) {
//        cout << "IP Model is NULL!" << endl;
//        return 1;
//    }
//
//    double gap;
//
//    gap = solIP.getOpt()-solLP.getOpt();
//
//    cout << "GAP " << printDouble(gap) << endl;
//
////    Free Memory
//    delete solverIP;
//    delete solverLP;
//    delete inst;
//    delete model;
//    delete env;
//    return 0;
//}
