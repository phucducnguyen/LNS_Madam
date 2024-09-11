
#include "mul_unit.h"

// void multiply(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result) {
// // Implement multiplication of LNS numbers
// #pragma HLS PIPELINE II=1
// #pragma HLS INTERFACE ap_ctrl_none port=return
// #pragma HLS INTERFACE ap_none port=a
// #pragma HLS INTERFACE ap_none port=b
// #pragma HLS INTERFACE ap_none port=result

//     // XOR to determine the sign of the result
//     sign_t result_sign = a.sign ^ b.sign;

//     // Simple addition of exponents (not the complete LNS multiplication logic)
//     exponent_t result_exp = a.exponent + b.exponent;

//     // Write the result back to the reference parameter
//     result = LNS<B, Q, R, Gamma>(result_sign, result_exp);
// }

void multiply(const LNS<B, Q, R, Gamma> a[N], const LNS<B, Q, R, Gamma> b[N], LNS<B, Q, R, Gamma> result[N]) {
// Implement multiplication of LNS numbers
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=a
#pragma HLS INTERFACE ap_none port=b
#pragma HLS INTERFACE ap_none port=result

    for (int i=0; i<N; i++){
#pragma HLS UNROLL
        // XOR to determine the sign of the result
        sign_t result_sign = a[i].sign ^ b[i].sign;

        // Simple addition of exponents (not the complete LNS multiplication logic)
        exponent_t result_exp = a[i].exponent + b[i].exponent;

        // Write the result back to the reference parameter
        result[i] = LNS<B, Q, R, Gamma>(result_sign, result_exp);
    }
}
