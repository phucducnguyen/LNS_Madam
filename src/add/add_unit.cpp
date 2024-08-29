// #include "LNS_datatype.h" // Ensure this header file includes LNS class definition

#include "add_unit.h"

void add(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result) {
// Implement multiplication of LNS numbers
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_none port=a
#pragma HLS INTERFACE ap_none port=b
#pragma HLS INTERFACE ap_none port=result

}
