#include "add_unit.h"
#include <iostream>

// float mitchell_LUT_base8[8]={0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875};
// float log2_LUT_base8[8]={1, 1.09051, 1.18921, 1.29684, 1.41421, 1.54221, 1.68179, 1.83401};
// float shift_3bit_log2_LUT_base8[8]={8, 8.72408, 9.51368, 10.37472, 11.31368, 12.33768, 13.45432, 14.67208}; 
int shift_8bit_log2_LUT_base8[8]={256, 279, 304, 332, 362, 394, 431, 470}; // need 9 bits to store

// Compare the input with the values inside a LUT to find the position of the closest value
int index_of_closest_value(int input_value, int LUT[Gamma]) {
    #pragma HLS ARRAY_PARTITION variable=LUT complete dim=1 // Partition the LUT for parallel access

    int closest_index = 0;
    int min_diff = abs(input_value - LUT[0]); // Initialize to maximum integer value
    
    // Iterate through the LUT array to find the closest value
    for (int i = 0; i < Gamma; i++) {
// #pragma HLS UNROLL
        int diff = abs(input_value - LUT[i]);
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
void sorting_and_shift(LNS<B, Q, R, Gamma> input[N], hls::stream<sum_t> out_stream[M]) {

    for (int i=0; i<N; i++){
// #pragma HLS UNROLL factor=4
        // Positive: index from 0 to 7  -  Negative: index from 8 to 15
        int index = (input[i].sign == 0) ? int(input[i].remainder) : Gamma + int(input[i].remainder);
        out_stream[index].write(1<<input[i].quotient);
    }
}

// Partial Sums Accumulator: Accumulates contributions from the array into a partial sum
void partial_sum_accumulator(hls::stream<sum_t> in_stream[M], sum_t partial_sum[M]) {

    // Accumulate values from each input stream
    for (int i = 0; i < M; i++) {
// #pragma HLS UNROLL //factor=4
        if (!in_stream[i].empty()) {
            sum_t value = in_stream[i].read();
            // std::cout << "value(" << value << ")" << std::endl;
            partial_sum[i] += value;  // Accumulate the value
        }
    }
}

void sort_shift_accumulate(LNS<B, Q, R, Gamma> input[N],sum_t partial_sum[M]){
    #pragma HLS ARRAY_PARTITION variable=partial_sum complete dim=1 // Enables parallel access to partial_sum
    for (int i=0; i<N; i++){
        // Positive: index from 0 to 7  -  Negative: index from 8 to 15
        ap_uint<4> sign_offset  = input[i].sign ? Gamma : 0;  ;
        ap_uint<6> index = input[i].remainder + sign_offset;      
        partial_sum[index] += (1<<input[i].quotient);
    }
}

// Scale the partial
// Using LUT to store shift-by-8 Mitchell approx - to reduce computation the use of DSP
void scale_back_mitchell_shift8(sum_t partial_sum[M], mul_t partial_sum_scale[M]){
    #pragma HLS ARRAY_PARTITION variable=partial_sum complete dim=1
    #pragma HLS ARRAY_PARTITION variable=partial_sum_scale complete dim=1
    #pragma HLS ARRAY_PARTITION variable=shift_8bit_log2_LUT_base8 complete dim=1

    for (int i = 0; i < M; i++) {
        #pragma HLS BIND_OP variable=partial_sum_scale op=mul impl=fabric latency=-1
        // Scaling back with a predefined lookup table for the shift values
        partial_sum_scale[i] = partial_sum[i] * shift_8bit_log2_LUT_base8[i % 8];
        std::cout << "partial_sum_scale["<<i<<"] = " << partial_sum_scale[i] << std::endl;
    }
}

// Partial Sums Generation Unit: Orchestrates sorting and accumulation
void partial_sums_generation_unit(LNS<B, Q, R, Gamma> inputs[N], mul_t partial_sum_results[M]) {

    hls::stream<sum_t> out_sort_shift[M];
    sum_t partial_sum[M]={0};

    sort_shift_accumulate(inputs, partial_sum);
    scale_back_mitchell_shift8(partial_sum,partial_sum_results);
}

// Add all scaled values - Big Sum
void addition_unit(mul_t partial_sum_accumulator_out[M], add_unit_t &final_sum) {
    #pragma HLS ARRAY_PARTITION variable=partial_sum_accumulator_out complete dim=1 // Enables parallel access to array 

    add_unit_t positive_sum = 0;
    add_unit_t negative_sum = 0;

    // Process positive and negative sums in parallel
    for (int i = 0; i < (M >> 1); i++) {
        #pragma HLS UNROLL // Unroll for increased performance
        positive_sum += partial_sum_accumulator_out[i];
        negative_sum -= partial_sum_accumulator_out[i + (M >> 1)];
    }

    final_sum = positive_sum + negative_sum;
    std::cout << "final_sum before scale back = " << final_sum << std::endl;
}

// Convert Int values back to Log values
void convertback(add_unit_t &sum, LNS<B, Q, R, Gamma> &final_sum){
    #pragma HLS PIPELINE II=1 // must have

    //Scale back to original with no Scale
    const int n = 8;
    const int SCALE_FACTOR = 1<<n;
    mul_t abs_value;
    ap_uint<5> leading_one_pos;
    quotient_t q;
    mul_t aligned_value;
    mul_t LUT_value;
    remainder_t r;


    // Handle zero case
    if (sum == 0){//static_cast<add_unit_t>(0.0)) {
        final_sum = LNS<B, Q, R, Gamma>(0, 0, 0);  // Zero case
        return;
    }
    // Extract sign
    sign_t s = sum < 0 ? 1 : 0;

    // Use integer approximation to calculate exponent
    abs_value = hls::fabs(sum);

    // Find the leading one position
    leading_one_pos = (abs_value == 0) ? 0 : (sizeof(abs_value) * 8 - __builtin_clz(abs_value) - 1);
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
void adder(LNS<B, Q, R, Gamma> inputs[N], LNS<B, Q, R, Gamma> &final_sum) {
// #pragma HLS PIPELINE
    sum_t partial_sum[M]={0};
    #pragma HLS ARRAY_PARTITION variable=partial_sum complete
    mul_t partial_sum_results[M];
    add_unit_t final_sum_int=0;
    
    ////////////////////////////////////
    sort_shift_accumulate(inputs, partial_sum);
    scale_back_mitchell_shift8(partial_sum,partial_sum_results);
    ////////////////////////////////////
    
    addition_unit(partial_sum_results, final_sum_int);

    // Convert final sum to LNS format
    convertback(final_sum_int, final_sum);
    
}