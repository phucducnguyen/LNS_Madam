
#include "mac.h"

void mac(LNS<B, Q, R, Gamma> array_input_a[N], LNS<B, Q, R, Gamma> array_input_b[N], LNS<B, Q, R, Gamma> &result){
#pragma HLS PIPELINE II=1
    LNS<B, Q, R, Gamma> multiplier_result[N];

    multiply(array_input_a, array_input_b, multiplier_result);
    adder(multiplier_result, result);
}