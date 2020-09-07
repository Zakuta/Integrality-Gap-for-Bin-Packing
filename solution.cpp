#ifndef SOLUTION_FUNCTIONS
#include "solution.h"

template<>
bool Solution<double>::printToStream(ostream &output, BPInstance *test) {
    for(unsigned i = 0; i< size; i++) {
        if(!isZero(coefficients[i],1e4)) {
            output << printDouble( coefficients[i] )<< " * " << "[ ";
            for(unsigned j = 0; j < (pattern[i]).size(); j++) {
                if(test->getMult(j) > 0) {
                    output << pattern[i][j] << ", ";
                }
            }
            output << "]" << endl;
            if(!output.good()) return false;
        }
    }
    return true;
}
#else
#define LP 0
#define SIMPLE_IP 1
#define MOD_KANTO_IP 2
using namespace std;

template <typename T>
Solution<T>::Solution() : coefficients(0,0), pattern(0,vector<unsigned>()), size(0){}

template <typename T>
Solution<T>::Solution(unsigned n) : coefficients(n,0), pattern(n,vector<unsigned>()), size(n){}

template <typename T>
T Solution<T>::getOpt(){
    return opt;
}
template <typename T>
T Solution<T>::getCoefficient(unsigned i){
    return coefficients[i];
}
template <typename T>
vector<unsigned> Solution<T>::getPattern(unsigned i){
    return pattern[i];
}
template <typename T>
unsigned Solution<T>::getSize(){
    return size;
}

template <typename T>
void Solution<T>::setOpt(T value){opt = value;}
template <typename T>
void Solution<T>::setCoeff(unsigned i, double x){coefficients[i] = x;}
template <typename T>
void Solution<T>::setPattern(unsigned i,vector<unsigned> p){pattern[i] = p;}
template <typename T>
void Solution<T>::setPatternat(unsigned i, unsigned j, unsigned p){pattern[i][j] = p;}
template <typename T>
void Solution<T>::resizePattern(unsigned i, unsigned n){pattern[i].resize(n);}
template <typename T>
void Solution<T>::resizeAll(unsigned k){pattern.resize(k); coefficients.resize(k); size = k;}

template <typename T>
void Solution<T>::saveSolution(GRBModel * model, BPInstance * test, unsigned kind)
{
    if(kind == LP) {
        opt = model->get(GRB_DoubleAttr_ObjVal);
        unsigned varNumber = model->get(GRB_IntAttr_NumVars);
        unsigned k = 0;
        if(size < test->getNrOfItems()) {
            resizeAll(test->getNrOfItems());
        }
        for(unsigned i = 0; i < varNumber; i++) {
            GRBVar b = model->getVarByName(NumberToString(i));
            if(b.get(GRB_IntAttr_VBasis) == 0) {
                if(!isZero(b.get(GRB_DoubleAttr_X),1e4)) {
                    coefficients[k]=b.get(GRB_DoubleAttr_X);
                    pattern[k].resize(test->getNrOfItems());
                    for(unsigned j = 0; j < test->getNrOfItems(); j++) {
                        pattern[k][j] = almostIntToInt(model->getCoeff(model->getConstrByName(NumberToString(j)),b));
                    }
                    k++;
                }
            }
        }
        resizeAll(k);
        return;
    } else {
        if (kind == SIMPLE_IP) {
            unsigned currPosInCoeff = 0;
            opt = almostIntToInt(model->get(GRB_DoubleAttr_ObjVal));
            resizeAll(opt);
            unsigned varNumber = model->get(GRB_IntAttr_NumVars);
            for(unsigned currVar = 0; currVar < varNumber; currVar++) {
                GRBVar b = model->getVarByName(NumberToString(currVar));
                if(almostIntToInt(b.get(GRB_DoubleAttr_X)) != 0) {
                    coefficients[currPosInCoeff] = almostIntToInt(b.get(GRB_DoubleAttr_X));
                    pattern[currPosInCoeff].resize(test->getNrOfItems());
                    for(unsigned j = 0; j < test->getNrOfItems(); j++) {
                        if(test->getMult(j) > 0 ) {
                            pattern[currPosInCoeff][j] = almostIntToInt(model->getCoeff(model->getConstrByName(NumberToString(j)),b));
                        } else {
                            pattern[currPosInCoeff][j] = 0;
                        }
                    }
                    currPosInCoeff++;
                }
            }
            resizeAll(currPosInCoeff);
            return;
        } else {
            resizeAll(opt);
            for(unsigned currPosInCoeff = 0; currPosInCoeff < opt; currPosInCoeff++) {
                unsigned j;
                coefficients[currPosInCoeff] = 1;
                pattern[currPosInCoeff].resize(test->getNrOfItems());
                unsigned currPosInPattern = 0;
                for(j = 0; j < test->getNrOfItems(); j++) {
                    if(test->getMult(j) != 0) {
                        GRBVar b  = model->getVarByName("Bin "+NumberToString(currPosInCoeff)+" Item "+NumberToString(currPosInPattern));
                        pattern[currPosInCoeff][j] = almostIntToInt(b.get(GRB_DoubleAttr_X));
                        currPosInPattern++;
                    } else {
                        pattern[currPosInCoeff][j] = 0;
                    }
                }
            }
        }
    }
}

template<typename T>
bool Solution<T>::printToStream(ostream & output, BPInstance * test) {
    for(unsigned i = 0; i< size; i++) {
        if(!isZero(coefficients[i],100)) {
            output << coefficients[i] << " * " << "[ ";
            for(unsigned j = 0; j < (pattern[i]).size(); j++) {
                if(test->getMult(j) > 0) {
                    output << pattern[i][j] << ", ";
                }
            }
            output << "]" << endl;
            if(!output.good()) return false;
        }
    }
    return true;
}


#endif

