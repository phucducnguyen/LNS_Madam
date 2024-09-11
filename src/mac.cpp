
#include "mac.h"

void mac(LNS<B, Q, R, Gamma> array_input_a[N], LNS<B, Q, R, Gamma> array_input_b[N], LNS<B, Q, R, Gamma> &result){
#pragma HLS PIPELINE II=1
    LNS<B, Q, R, Gamma> multiplier_result[N];

//     for (int i =0; i < N; i++){
// #pragma HLS UNROLL
//         multiply(array_input_a[i], array_input_b[i], multiplier_result[i]);
//         // std::cout << "multiplier_result(" << multiplier_result[i].sign << "," << multiplier_result[i].quotient << "," << multiplier_result[i].remainder <<")" << std::endl;
//    }
    multiply(array_input_a, array_input_b, multiplier_result);
    adder(multiplier_result, result);
}