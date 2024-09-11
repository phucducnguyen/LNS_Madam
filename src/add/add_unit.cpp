#include "add_unit.h"

// Lookup table for 2^(i/GAMMA)
float lookup_table[N];

// Function to initialize the lookup table
void initialize_lut() {
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        lookup_table[i] = hls::powf(2.0f, (float)i / 8);
    }
}

// Sorting Unit: Outputs contributions based on quotient and remainder to specific array element
void sorting_and_shift(LNS<B, Q, R, Gamma> input, hls::stream<sum_t> out_stream[M]) {
#pragma HLS PIPELINE II=1
#pragma HLS STREAM variable=out_stream
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=input bundle=control
#pragma HLS INTERFACE axis port=out_stream

    int index = (input.sign == 0) ? int(input.remainder) : Gamma + int(input.remainder);
    
    for (int i = 0; i < M; ++i) {
        #pragma HLS UNROLL
        out_stream[i].write((index == i) ? (1 << input.quotient) : 0);
    }
}

// Partial Sums Accumulator: Accumulates contributions from the array into a partial sum
void partial_sum_accumulator(hls::stream<sum_t> in_stream[M], sum_t partial_sum[M]) {
#pragma HLS PIPELINE II=1
#pragma HLS STREAM variable=in_stream
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE s_axilite port=partial_sum bundle=control

    // Accumulate values from each input stream
    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL
        if (!in_stream[i].empty()) {
            sum_t value = in_stream[i].read();
            partial_sum[i] += value;  // Accumulate the value
        }
    }
}
void scale_back(sum_t partial_sum[M], float partial_sum_scale[M]){
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=partial_sum bundle=control
#pragma HLS INTERFACE s_axilite port=partial_sum_scale bundle=control

    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL
        float exponent = (float)(i % Gamma) / (float)(Gamma);
        partial_sum_scale[i] = partial_sum[i] * hls::powf(2.0f, exponent);
    }
}

// Partial Sums Generation Unit: Orchestrates sorting and accumulation
void partial_sums_generation_unit(LNS<B, Q, R, Gamma> inputs[N], float partial_sum_results[M]) { //quotient_t quotients[N], remainder_t remainders[N],
#pragma HLS PIPELINE II=1

    hls::stream<sum_t> out_sort_shift[M];
#pragma HLS STREAM variable=out_sort_shift depth=M
#pragma HLS ARRAY_PARTITION variable=out_sort_shift complete dim=1

    sum_t partial_sum[M];
#pragma HLS ARRAY_PARTITION variable=partial_sum complete dim=1

    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL
        partial_sum[i] = 0;
    }

    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        std::cout << "inputs (" << inputs[i].sign << "," << inputs[i].quotient << "," << inputs[i].remainder << ")" << std::endl;
        
        // Sorting and accumulation of partial sums
        sorting_and_shift(inputs[i], out_sort_shift);
        
        // Process each partial sum independently
        partial_sum_accumulator(out_sort_shift, partial_sum); // Accumulate each stream's values
    }
    scale_back(partial_sum,partial_sum_results);
}

void addition_unit(float partial_sum_accumulator_out[M], float &final_sum) {
#pragma HLS PIPELINE II=1

    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL
        // final_sum += partial_sum_accumulator_out[i];
        final_sum += (i < 8) ? partial_sum_accumulator_out[i] : -partial_sum_accumulator_out[i];
    }
}


void convertback(float &sum, LNS<B, Q, R, Gamma> &final_sum){
    final_sum = LNS<B, Q, R, Gamma>::from_float(sum);
}

// void convert_to_float(float &sum, LNS<B, Q, R, Gamma> &final_sum){
//     sum = final_sum.to_float();
// }

// Main adder function
void adder(LNS<B, Q, R, Gamma> inputs[N], LNS<B, Q, R, Gamma> &final_sum) { // quotient_t quotients[N], remainder_t remainders[N],
// #pragma HLS DATAFLOW
#pragma HLS PIPELINE II=1
    
    float partial_sum_results[M];
#pragma HLS ARRAY_PARTITION variable=partial_sum_results complete dim=1

    float final_sum_float=0;
    
    // Generate partial sums
    partial_sums_generation_unit(inputs, partial_sum_results);

    for (int i=0; i<M; i++){
        std::cout << "partial_sum_results =" << partial_sum_results[i] << std::endl;
    }
    // Compute the final sum
    addition_unit(partial_sum_results, final_sum_float);

    // std::cout << "final_sum_float =" << final_sum_float << std::endl;

    // Convert final sum to LNS format
    convertback(final_sum_float, final_sum);
    
}