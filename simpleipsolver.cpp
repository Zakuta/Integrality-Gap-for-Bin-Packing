#include "simpleipsolver.h"
#include "helper.h"

#define TYPE 1

GRBModel * SimpleIPSolver::buildAndSolve(const std::vector<double> &sizeVector, GRBModel * model,
                                         Solution<unsigned> & sol, GRBEnv * env)
{
    try{
        unsigned nrOfItems = sizeVector.size();
        model->reset();                                                         //resets model to pre-optimized state
        unsigned varNumber = model->get(GRB_IntAttr_NumVars);                   //get number of variables in model
        for(unsigned i = 0; i < varNumber; i++) {
            model->getVarByName(NumberToString(i)).set(GRB_CharAttr_VType,'I'); //set each variable to integer
        }
        for(unsigned i = 0; i < nrOfItems; i++) {
            model->getConstrByName(NumberToString(i)).set(GRB_CharAttr_Sense, GRB_GREATER_EQUAL);
        }
        model->update();
        model->optimize();                                                      //optimize

        sol.saveSolution(model, sizeVector, TYPE);                                      //save the solution

        return model;
    } catch(GRBException e) {
        cout << "Exception during modify" << endl;
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
        return nullptr;
    } catch(exception e){
        cout << e.what()<< endl;
        return nullptr;
    } catch(...) {
        cout << "Exception during modify" << endl;
        return nullptr;
    }
}
