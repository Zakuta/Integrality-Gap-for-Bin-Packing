#include "src/AIG_BP.hpp"

int main() {
//    vector<double> sizeVector = {0.109375, 0.109375, 0.16145833, 0.17708333, 0.24479167, 0.25, 0.26041667, 0.34375,
//                                 0.39583333, 0.39583333, 0.5, 0.5, 0.5, 0.50520833, 0.50520833, 0.578125, 0.66145833,
//                                 0.74479167, 0.76041667};

	AIG_BP aig_bp;
	aig_bp.IOHprofiler_set_number_of_variables(17);


    vector<double> sizeVector = {0.12,0.12,0.165,0.18,0.245,0.25,0.26,0.35,0.39,0.5,0.5,0.5,
    0.505,0.575,0.655,0.75,0.76};

    cout << aig_bp.evaluate(sizeVector) << endl;
    return 0;
}