#include "helper.h"

bool isZero(double number, int multiplicator){
    if(number >= multiplicator*numeric_limits<double>::epsilon() || number <= -multiplicator*numeric_limits<double>::epsilon()) {
        return false;
    } else {
        return true;
    }
}

bool isLargerEqualZero(double number, int multiplicator) {
    if(number >= -multiplicator*numeric_limits<double>::epsilon()){
        return true;
    } else {
        return false;
    }
}

string printDouble(double number) {
    string output;
    if(isZero(number,1e4)) {
        output = NumberToString(0);
    } else {
        output = NumberToString(number);
    }
    return output;
}

int almostIntToInt(double x) {
    return floor(x + 1e-6);
}


void setEnvParams(GRBEnv * env, unsigned loud, unsigned memory)
{
    env->set(GRB_IntParam_OutputFlag, loud);
    if(memory) {
        env->set(GRB_DoubleParam_NodefileStart,1);
        env->set(GRB_IntParam_Threads, 1);
    }
    env->set(GRB_IntParam_Method, 1);
    env->set(GRB_IntParam_Presolve, 0);
    env->set(GRB_DoubleParam_IntFeasTol,1e-9);
}
