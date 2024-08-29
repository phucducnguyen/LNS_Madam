#include "add_unit.h"

// Sorting Unit
void sorting_unit(quotient_t quotient, remainder_t remainder, hls::stream<sum_t> partial_sums[N]) {
#pragma HLS INLINE
#pragma HLS ARRAY_PARTITION variable=partial_sums complete dim=1
    sum_t quotient_contribution = (1 << quotient); // Generate contribution by shifting 1 by quotient value
    partial_sums[remainder].write(quotient_contribution); // Route contribution to the correct partial sum accumulator
}

// Partial Sums Accumulator
void partial_sum_accumulator(hls::stream<sum_t> partial_sums[N], sum_t &result_sum) {
#pragma HLS INLINE
    sum_t temp_sum = 0;
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        temp_sum += partial_sums[i].read(); // Accumulate all partial sums
    }
    result_sum = temp_sum;
}

// Partial Sums Generation Unit
void add(quotient_t quotients[N], remainder_t remainders[N], sum_t &final_sum) {
#pragma HLS DATAFLOW

    hls::stream<sum_t> partial_sums[N];
#pragma HLS STREAM variable=partial_sums depth=2

    // Sorting and accumulation of partial sums
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        sorting_unit(quotients[i], remainders[i], partial_sums); // Sort quotient contributions
    }

    partial_sum_accumulator(partial_sums, final_sum); // Accumulate the sorted partial sums
}


// void add(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result) {
// // Implement multiplication of LNS numbers
// #pragma HLS PIPELINE II=1
// #pragma HLS INTERFACE ap_ctrl_none port=return
// #pragma HLS INTERFACE ap_none port=a
// #pragma HLS INTERFACE ap_none port=b
// #pragma HLS INTERFACE ap_none port=result

// }


