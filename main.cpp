#include "arguments.h"
#include "simpleipsolver.h"
#include "simplelpsolver.h"


int main(int argc, char *argv[])
{
    OPTIONS args;
    args = parseargs(argc,argv);
    if(!args.succeededToReadArguments) {
        cout << "Failed to read program's arguments. Exiting..." << endl;
        return 1;
    }
    BPInstance *inst;
    if(!args.quiet) {
        cout << "Generating Instance..." << endl;
    }
    if(!args.random) {
        inst = new BPInstance(args.inFile);
    }

    Solver<double> *solverLP;
    if(!args.quiet) {
        cout << "Build and solve LP...";
    }
    solverLP = new SimpleLPSolver();

    Solution<double> solLP(inst->getNrOfItems());

    GRBEnv *env = new GRBEnv();
    setEnvParams(env, args.loud, args.nodefiles);
    GRBModel *model = new GRBModel(*env);
    model = solverLP->buildAndSolve(inst,model,solLP, env);

    if(model == NULL) {
        cout << "LP Model is NULL!" << endl;
        return 1;
    }
    if(!args.quiet) {
        cout << " Finished." << endl;
    }

    Solver<unsigned> *solverIP;
    Solution<unsigned> solIP;

    if(!args.quiet) {
        cout << "Build and solve IP...";
    }

    solverIP = new SimpleIPSolver();

    model = solverIP->buildAndSolve(inst,model,solIP, env);
    if(!args.quiet) {
        cout << " Finished." << endl;
    }
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
