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
void sorting_unit(quotient_t quotient, remainder_t remainder, sum_t out_sums[N]) {
    #pragma HLS INLINE
    #pragma HLS ARRAY_PARTITION variable=out_sums complete dim=1

    // Generate contribution by shifting 1 by quotient value
    sum_t quotient_contribution = (1 << quotient);

    // Route contribution to the correct partial sum accumulator
    if (remainder < N) {
        out_sums[remainder] = quotient_contribution;
    }
}

// Partial Sums Accumulator: Accumulates contributions from the array into a partial sum
void partial_sum_accumulator(float lut[N], sum_t input_sums[N], float partial_sum[N]) {
#pragma HLS INLINE
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=input_sums complete dim=1
    initialize_lut();
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        // Accumulate input sums into partial_sum
        partial_sum[i] = input_sums[i] * lut[i];
    }
}

// Partial Sums Generation Unit: Orchestrates sorting and accumulation
void partial_sums_generation_unit(quotient_t quotients[N], remainder_t remainders[N], float partial_sum_results[N]) {
#pragma HLS DATAFLOW

    sum_t partial_sums[N] = {0}; // Array to hold partial sums
#pragma HLS ARRAY_PARTITION variable=partial_sums complete dim=1

    // Sorting and accumulation of partial sums
    sorting_unit(quotient, remainder, partial_sums);

    // Process each partial sum independently
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        partial_sum_accumulator(lookup_table, partial_sums, partial_sum_results); // Accumulate each stream's values
    }
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

template<int B, int Q, int R, int Gamma>
void convertback(float sum, LNS<B, Q, R, Gamma> &final_sum){
    final_sum = LNS<B, Q, R, Gamma>::from_float(sum);
}

// Main adder function
template<int B, int Q, int R, int Gamma>
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
    convertback<B, Q, R, Gamma>(final_sum_float, final_sum);
}