#include "add_unit.h"
#include <iostream>

float mitchell_LUT_base8[8]={0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875};
float log2_LUT_base8[8]={1, 1.09051, 1.18921, 1.29684, 1.41421, 1.54221, 1.68179, 1.83401};
float shift_3bit_log2_LUT_base8[8]={8, 8.72408, 9.51368, 10.37472, 11.31368, 12.33768, 13.45432, 14.67208}; 
int shift_8bit_log2_LUT_base8[8]={256, 279, 304, 332, 362, 394, 431, 470}; // need 9 bits to store

// mul_t shift_and_add(sum_t x, sum_t y) {
//     mul_t result = 0;
//     #pragma HLS PIPELINE  // Enable pipelining
//     while (y > 0) {
//         if (y & 1) {
//             result += x;
//         }
//         x <<= 1;
//         y >>= 1;
//     }
//     return result;
// }

// Compare the input with the values inside a LUT to find the position of the closest value
int index_of_closest_value(int input_value, int LUT[Gamma]) {
    int closest_index = -1;
    int min_diff = 10000; // Initialize to maximum integer value
    int diff=0;
    // Iterate through the LUT array to find the closest value
    for (int i = 0; i < Gamma; i++) {
#pragma HLS UNROLL
        diff = abs(input_value - LUT[i]);
        if (diff < min_diff) {
            min_diff = diff;
            closest_index = i;
            // std::cout << "min_diff =" << min_diff << std::endl;
            // std::cout << "closest_index =" << closest_index << std::endl;
        }
    }
    return closest_index; // Return the index of the closest LUT value
}

// Sorting Unit: Outputs contributions based on quotient and remainder to specific array element
void sorting_and_shift(LNS<B, Q, R, Gamma> input, hls::stream<sum_t> out_stream[M]) {
#pragma HLS PIPELINE II=1
#pragma HLS STREAM variable=out_stream depth=4
// #pragma HLS INTERFACE ap_ctrl_none port=return
// #pragma HLS INTERFACE s_axilite port=input bundle=control
// #pragma HLS INTERFACE axis port=out_stream

    // Positive: index from 0 to 7  -  Negative: index from 8 to 15
    int index = (input.sign == 0) ? int(input.remainder) : Gamma + int(input.remainder);
    
    for (int i = 0; i < M; ++i) {
#pragma HLS UNROLL factor=4
        out_stream[i].write((index == i) ? (1 << input.quotient) : 0);
    }
}

// Partial Sums Accumulator: Accumulates contributions from the array into a partial sum
void partial_sum_accumulator(hls::stream<sum_t> in_stream[M], sum_t partial_sum[M]) {
#pragma HLS PIPELINE II=1
#pragma HLS STREAM variable=in_stream depth=4
// #pragma HLS INTERFACE ap_ctrl_none port=return
// #pragma HLS INTERFACE axis port=in_stream
// #pragma HLS INTERFACE s_axilite port=partial_sum bundle=control

    // Accumulate values from each input stream
    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL factor=4
        if (!in_stream[i].empty()) {
            sum_t value = in_stream[i].read();
            std::cout << "value(" << value << ")" << std::endl;
            partial_sum[i] += value;  // Accumulate the value
        }
    }
}

// Scale the partial
// Using LUT to store shift-by-8 Mitchell approx - to reduce computation / the use of DSP
void scale_back_mitchell_shift8(sum_t partial_sum[M], mul_t partial_sum_scale[M]){
#pragma HLS PIPELINE II=1
// #pragma HLS INTERFACE ap_ctrl_none port=return
// #pragma HLS INTERFACE s_axilite port=partial_sum bundle=control
// #pragma HLS INTERFACE s_axilite port=partial_sum_scale bundle=control

    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL factor=4       
#pragma HLS BIND_OP variable=partial_sum_scale op=mul  impl=fabric latency=-1 // subpress the use of DSP for variable partial_sum_cale - operation=mul
        partial_sum_scale[i] = (partial_sum[i]* shift_8bit_log2_LUT_base8[i%8]);
    }
}

// Experiment: mitchell - very large quantization error
void scale_back_mitchell(sum_t partial_sum[M], sum_t partial_sum_scale[M]){
#pragma HLS PIPELINE II=1
// #pragma HLS INTERFACE ap_ctrl_none port=return
// #pragma HLS INTERFACE s_axilite port=partial_sum bundle=control
// #pragma HLS INTERFACE s_axilite port=partial_sum_scale bundle=control
#pragma HLS BIND_OP variable=partial_sum_scale op=mul  impl=fabric latency=-1

    const int n = 3;
    const int SCALE_FACTOR = (1<<n); // 102
    float exponent =0;

    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL factor=2
        // Calculate exponent in fixed-point (scaled by SCALE_FACTOR)
        exponent = mitchell_LUT_base8[i%Gamma];

        // Apply Mitchell approximation in integer arithmetic:
        float approx_pow2 = 1 + exponent;

        // Scale the partial sum using the approximated value in fixed-point
        partial_sum_scale[i] = (partial_sum[i] * sum_t(approx_pow2 * SCALE_FACTOR)); // Shift to correct for SCALE_FACTOR
        // std::cout << "approx_pow2 * SCALE_FACTOR(" << approx_pow2 * SCALE_FACTOR << ")" << std::endl;
        // std::cout << "partial_sum(" << partial_sum[i] << ")" << std::endl;
        std::cout << "partial_sum_scale(" << partial_sum_scale[i] << ")" << std::endl;
    }
}

// Partial Sums Generation Unit: Orchestrates sorting and accumulation
void partial_sums_generation_unit(LNS<B, Q, R, Gamma> inputs[N], mul_t partial_sum_results[M]) {
#pragma HLS PIPELINE II=1

    hls::stream<sum_t> out_sort_shift[M];
#pragma HLS STREAM variable=out_sort_shift depth=4
#pragma HLS ARRAY_PARTITION variable=out_sort_shift cyclic factor=P

    sum_t partial_sum[M];
#pragma HLS ARRAY_PARTITION variable=partial_sum cyclic factor=P

    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL factor=4
        partial_sum[i] = 0;
    }

    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL factor=4
        std::cout << "inputs (" << inputs[i].sign << "," << inputs[i].quotient << "," << inputs[i].remainder << ")" << std::endl;
        
        // Sorting and accumulation of partial sums
        sorting_and_shift(inputs[i], out_sort_shift);
        
        // Process each partial sum independently
        partial_sum_accumulator(out_sort_shift, partial_sum); // Accumulate each stream's values
    }
    scale_back_mitchell_shift8(partial_sum,partial_sum_results);
    // scale_back_mitchell(partial_sum,partial_sum_results);
}

// Add all scaled values - Big Sum
void addition_unit(mul_t partial_sum_accumulator_out[M], add_unit_t &final_sum) { //sum_t &final_sum
#pragma HLS PIPELINE II=1
// #pragma HLS BIND_OP variable=final_sum op=fadd  impl=fabric latency=-1

    for (int i = 0; i < M; i++) {
#pragma HLS UNROLL factor=4
        // final_sum += partial_sum_accumulator_out[i];
        // final_sum += (i < 8) ? partial_sum_accumulator_out[i] : -partial_sum_accumulator_out[i];
        if (i<8){
            final_sum = final_sum + partial_sum_accumulator_out[i];
        } else {
            final_sum = final_sum - partial_sum_accumulator_out[i];
        }        
    }
}

// Convert Int values back to Log values
void convertback(add_unit_t &sum, LNS<B, Q, R, Gamma> &final_sum){

    //Scale back to original with no Scale
    const int n = 8;
    const int SCALE_FACTOR = 1<<n;

    // Handle zero case
    if (sum == static_cast<add_unit_t>(0.0)) {
        final_sum = LNS<B, Q, R, Gamma>(0, 0, 0);  // Zero case
    }
    // Extract sign
    sign_t s = sum < 0 ? 1 : 0;

    // Use integer approximation to calculate exponent
    mul_t abs_value;
    mul_t aligned_value;
    mul_t LUT_value;

    quotient_t  q;
    remainder_t r;

    abs_value = hls::fabs(sum);

    // Find the leading one position
    ap_uint<5> leading_one_pos = (abs_value == 0) ? 0 : (sizeof(abs_value) * 8 - __builtin_clz(abs_value) - 1);
    // std::cout << "leading_one_pos = " << leading_one_pos << std::endl;
    std::cout << "leading_one_pos = " << leading_one_pos << std::endl;

    // Return back after shift
    q = leading_one_pos - ap_uint<4>(n); // 256 = 2^8 (shift back by 8)
    std::cout << "q = " << q << std::endl;

    // Shift left to remove leading zeros
    aligned_value = abs_value << (mul_t::width - 1 - leading_one_pos); // Shift to align the most significant 1 to the left
    std::cout << "aligned_value = " << aligned_value << std::endl;
    
    // Shift back to find remainder value
    // n+1 is needed to store remainder value
    // The shifted amount = total bit width - (n+1)
    LUT_value = aligned_value >> (mul_t::width - (n+1));   //need n+1 bit to store each value inside the LUT
    // std::cout << "shifted_value = " << shifted_value << std::endl;
    std::cout << "LUT_value = " << LUT_value << std::endl;

    // remainder = position of the closest value
    r = index_of_closest_value(LUT_value, shift_8bit_log2_LUT_base8);
    std::cout << "r = " << r << std::endl;

    final_sum = LNS<B, Q, R, Gamma>(s, q, r);
}



// Top-level adder function
void adder(LNS<B, Q, R, Gamma> inputs[N], LNS<B, Q, R, Gamma> &final_sum) { // quotient_t quotients[N], remainder_t remainders[N],
// #pragma HLS DATAFLOW
#pragma HLS PIPELINE II=1
    
    mul_t partial_sum_results[M];
// #pragma HLS ARRAY_PARTITION variable=partial_sum_results complete dim=1
#pragma HLS ARRAY_PARTITION variable=partial_sum_results cyclic factor=P

    add_unit_t final_sum_int=0;
    
    // Generate partial sums
    partial_sums_generation_unit(inputs, partial_sum_results);

    // for (int i=0; i<M; i++){
    //     std::cout << "partial_sum_results =" << partial_sum_results[i] << std::endl;
    // }
    // Compute the final sum
    addition_unit(partial_sum_results, final_sum_int);

    std::cout << "final_sum_int = " << final_sum_int << std::endl;

    // Convert final sum to LNS format
    convertback(final_sum_int, final_sum);
    std::cout << "final_sum = (" << final_sum.sign << "," << final_sum.quotient << "," << final_sum.remainder << ")" << std::endl;
    
}