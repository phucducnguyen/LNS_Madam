// #include "LNS_datatype.h" // Ensure this header file includes LNS class definition

#include "mul_unit.h"

void multiply(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result) {
// Implement multiplication of LNS numbers
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=a
#pragma HLS INTERFACE ap_none port=b
#pragma HLS INTERFACE ap_none port=result

    // XOR to determine the sign of the result
    ap_uint<1> result_sign = a.sign ^ b.sign;

    // Simple addition of exponents (not the complete LNS multiplication logic)
    ap_uint<B> result_exp = a.exponent + b.exponent;

    // Write the result back to the reference parameter
    result = LNS<B, Q, R, Gamma>(result_sign, result_exp);
}
