
#include "mul_unit.h"

void multiply(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result) {
    // // XOR to determine the sign of the result
    // sign_t result_sign = a.sign ^ b.sign;

    // // Simple addition of exponents (not the complete LNS multiplication logic)
    // exponent_t result_exp = a.exponent + b.exponent;

    // Write the result back to the reference parameter
    result = LNS<B, Q, R, Gamma>(a.sign ^ b.sign, a.exponent + b.exponent);
}

// Implement multiplication of LNS numbers
void multiply_array(const LNS<B, Q, R, Gamma> array_input_a[N], const LNS<B, Q, R, Gamma> array_input_b[N], LNS<B, Q, R, Gamma> result[N]) {
// #pragma HLS PIPELINE II=1 // do not put, increase latency and FF and LUT

    for (int i=0; i<N; i++){
// #pragma HLS UNROLL
        // // XOR to determine the sign of the result
        // sign_t result_sign = array_input_a[i].sign ^ array_input_b[i].sign;

        // // Simple addition of exponents (not the complete LNS multiplication logic)
        // exponent_t result_exp = array_input_a[i].exponent + array_input_b[i].exponent;

        // Write the result back to the reference parameter
        result[i] = LNS<B, Q, R, Gamma>(sign_t(array_input_a[i].sign ^ array_input_b[i].sign), 
                                    exponent_t(array_input_a[i].exponent + array_input_b[i].exponent));
    }
}
