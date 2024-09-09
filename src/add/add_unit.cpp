#include "add_unit.h"

// Lookup table for 2^(i/GAMMA)
float lookup_table[N];

// Function to initialize the lookup table
void initialize_lut() {
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        lookup_table[i] = hls::powf(2.0, (float)i / 8);
    }
}

// Sorting Unit: Outputs contributions based on quotient and remainder to specific array element
void sorting_unit(quotient_t quotient, remainder_t remainder, sum_t quotient_contribution) {
#pragma HLS INLINE
    // #pragma HLS ARRAY_PARTITION variable=out_sums complete dim=1

    // Generate contribution by shifting 1 by quotient value
    quotient_contribution = (1 << quotient);
    // // Route contribution to the correct partial sum accumulator
    // if (remainder < N) {
    //     out_sums[remainder] = quotient_contribution;
    // }
}

// Partial Sums Accumulator: Accumulates contributions from the array into a partial sum
void partial_sum_accumulator(remainder_t remainder, sum_t quotient_contribution, sum_t partial_sum[N]) {
#pragma HLS INLINE
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=partial_sum complete dim=1

    if (remainder < N) {
        partial_sum[remainder] += quotient_contribution;
    }
}

void multiplier(sum_t partial_sum[N], float partial_sum_scale[N]){
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        partial_sum_scale[i] = partial_sum[i] * hls::powf(2.0, (float)i / 8);
    }
    
}

// Partial Sums Generation Unit: Orchestrates sorting and accumulation
void partial_sums_generation_unit(quotient_t quotients[N], remainder_t remainders[N], float partial_sum_results[N]) {
#pragma HLS DATAFLOW

    sum_t quotient_contribution;
// #pragma HLS ARRAY_PARTITION variable=partial_sums complete dim=1
    sum_t partial_sum[N];
#pragma HLS ARRAY_PARTITION variable=partial_sum complete dim=1

    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        // Sorting and accumulation of partial sums
        sorting_unit(quotients[i], remainders[i], quotient_contribution);

        // Process each partial sum independently
        partial_sum_accumulator(remainders[i], quotient_contribution, partial_sum); // Accumulate each stream's values
    }

    multiplier(partial_sum,partial_sum_results);
}

void addition_unit(float partial_sum_accumulator_out[N], float &final_sum) {
#pragma HLS INLINE
    float sum = 0;
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        sum += partial_sum_accumulator_out[i];
    }
    final_sum = sum;
}


void convertback(float sum, LNS<B, Q, R, Gamma> &final_sum){
    final_sum = LNS<B, Q, R, Gamma>::from_float(sum);
}

// Main adder function
void adder(quotient_t quotients[N], remainder_t remainders[N], LNS<B, Q, R, Gamma> &final_sum) {
#pragma HLS DATAFLOW

    float partial_sum_results[N];
#pragma HLS ARRAY_PARTITION variable=partial_sum_results complete dim=1

    float final_sum_float;

    // Generate partial sums
    partial_sums_generation_unit(quotients, remainders, partial_sum_results);

    // Compute the final sum
    addition_unit(partial_sum_results, final_sum_float);

    // Convert final sum to LNS format
    convertback(final_sum_float, final_sum);
}