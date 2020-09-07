#include "simplelpsolver.h"
#include "helper.h"


GRBModel * SimpleLPSolver::buildAndSolve(BPInstance * inst, GRBModel * model,
                                         Solution<double> &sol, GRBEnv * env)
{
    try{
        vector<int> x(inst->getNrOfItems(),0);
        GRBLinExpr *lhs = new GRBLinExpr[inst->getNrOfItems()];
        unsigned varNumber = 0;
        unsigned& varNumberref = varNumber;

        for(unsigned i = 0; i < inst->getNrOfItems(); i++) {
            tryNewItem(inst,model,x,i,1,lhs, 1, varNumberref);
        }

        model->update();

        for(unsigned i = 0; i< inst->getNrOfItems(); i++) {
            model->addConstr(lhs[i], GRB_EQUAL,
                             inst->getMult(i), NumberToString(i));
        }

        delete[] lhs;

        model->update();
        model->optimize();

        sol.saveSolution(model,inst, LP);

        return model;

    } catch(GRBException e) {
        cout << "Exception during createVariables " << endl;
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
        return NULL;
    } catch(...) {
        cout << "Exception during createVariables " << endl;
        return NULL;
    }
}

void SimpleLPSolver::tryNewItem(BPInstance * inst, GRBModel * model,
                                vector<int>& x, int newItem, double restCap,
                                GRBLinExpr *lhsConstraints, int depth,
                                unsigned& varNumber) {
    try{
        for(unsigned i = 1; i <= 1./inst->getSize(newItem)+2; i++) {
            if(isLargerEqualZero(restCap-i*inst->getSize(newItem), depth+i+1)) {
                x[newItem] = i;
                for(unsigned k = newItem+1; k < inst->getNrOfItems(); k++){
                    tryNewItem(inst,model,x,k,
                               restCap-i*inst->getSize(newItem),
                               lhsConstraints, depth+i+1,varNumber
                    );
                }
            } else {
                if(i==1) {
                    break;
                }
                string sVarNumber= NumberToString(varNumber);
                x[newItem] = i-1;
                GRBVar newVar = model->addVar(0, 1e21, 1, GRB_CONTINUOUS, sVarNumber);
                for(unsigned j = 0; j < inst->getNrOfItems(); j++) {
                    lhsConstraints[j] += x[j]*newVar;
                }
                varNumber++;
                break;
            }
        }
        x[newItem] = 0;
    } catch(GRBException e) {
        cout << "Exception during tryNewItem " << endl;
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch(...) {
        cout << "Exception during tryNewItem" << endl;
    }
}
