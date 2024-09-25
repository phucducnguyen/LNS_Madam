
#include "mac.h"

void mac(LNS<B, Q, R, Gamma> array_input_a[N], LNS<B, Q, R, Gamma> array_input_b[N], LNS<B, Q, R, Gamma> &result){
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=array_input_a cyclic factor=4
#pragma HLS ARRAY_PARTITION variable=array_input_b cyclic factor=4
    LNS<B, Q, R, Gamma> multiplier_result[N];

    multiply(array_input_a, array_input_b, multiplier_result);
    adder(multiplier_result, result);
}