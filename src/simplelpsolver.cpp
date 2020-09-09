#include "simplelpsolver.h"
#include "helper.h"

#define TYPE 0


GRBModel * SimpleLPSolver::buildAndSolve(const std::vector<double> &sizeVector, GRBModel * model,
                                         Solution<double> &sol, GRBEnv * env)
{
    try{
        unsigned nrOfItems = sizeVector.size();
        vector<int> x(nrOfItems,0);
        GRBLinExpr *lhs = new GRBLinExpr[nrOfItems];
        unsigned varNumber = 0;
        unsigned& varNumberref = varNumber;

        for(unsigned i = 0; i < nrOfItems; i++) {
            tryNewItem(sizeVector, model,x, i,1,lhs, 1, varNumberref);
        }

        model->update();

        for(unsigned i = 0; i< nrOfItems; i++) {
            model->addConstr(lhs[i], GRB_EQUAL,
                             1, NumberToString(i));
        }

        delete[] lhs;

        model->update();
        model->optimize();

        sol.saveSolution(model, sizeVector, TYPE);

        return model;

    } catch(GRBException e) {
        cout << "Exception during createVariables " << endl;
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
        return nullptr;
    } catch(...) {
        cout << "Exception during createVariables " << endl;
        return nullptr;
    }
}

void SimpleLPSolver::tryNewItem(const std::vector<double> &sizeVector, GRBModel * model,
                                vector<int>& x, int newItem, double restCap,
                                GRBLinExpr *lhsConstraints, int depth,
                                unsigned& varNumber) {
    try{
        unsigned nrOfItems = sizeVector.size();
        for(unsigned i = 1; i <= 1./sizeVector[newItem]+2; i++) {
            if(isLargerEqualZero(restCap-i*sizeVector[newItem], depth+i+1)) {
                x[newItem] = i;
                for(unsigned k = newItem+1; k < nrOfItems; k++){
                    tryNewItem(sizeVector, model,x, k,
                               restCap-i*sizeVector[newItem],
                               lhsConstraints, depth+i+1, varNumber
                    );
                }
            } else {
                if(i==1) {
                    break;
                }
                string sVarNumber= NumberToString(varNumber);
                x[newItem] = i-1;
                GRBVar newVar = model->addVar(0, 1e21, 1, GRB_CONTINUOUS, sVarNumber);
                for(unsigned j = 0; j < nrOfItems; j++) {
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
