#include "simpleipsolver.h"
#include "helper.h"

#define TYPE 1

GRBModel * SimpleIPSolver::buildAndSolve(BPInstance * test, GRBModel * model,
                                         Solution<unsigned> & sol, GRBEnv * env)
{
    try{
        model->reset();                                                         //resets model to pre-optimized state
        unsigned varNumber = model->get(GRB_IntAttr_NumVars);                   //get number of variables in model
        for(unsigned i = 0; i < varNumber; i++) {
            model->getVarByName(NumberToString(i)).set(GRB_CharAttr_VType,'I'); //set each variable to integer
        }
        for(unsigned i = 0; i < test->getNrOfItems(); i++) {
            if(test->getMult(i)>0) {
                model->getConstrByName(NumberToString(i)).set(GRB_CharAttr_Sense, GRB_GREATER_EQUAL);
            }
        }
        model->update();
        model->optimize();                                                      //optimize

        sol.saveSolution(model,test,TYPE);                                      //save the solution

        return model;
    } catch(GRBException e) {
        cout << "Exception during modify" << endl;
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
        return NULL;
    } catch(exception e){
        cout << e.what()<< endl;
        return NULL;
    } catch(...) {
        cout << "Exception during modify" << endl;
        return NULL;
    }
}
