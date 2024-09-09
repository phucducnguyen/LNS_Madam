#ifndef ADD_UNIT_H
#define ADD_UNIT_H

#include "../LNS_datatype.h" // Ensure this header file includes LNS class definition

typedef ap_uint<16> sum_t;

extern "C" {
	// void add(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result);
	// Function to initialize the lookup table
	void initialize_lut();
	
	// Sorting Unit: Outputs contributions based on quotient and remainder
	void sorting_unit(quotient_t quotient, remainder_t remainder, sum_t quotient_contribution);

	// Partial Sums Accumulator: Accumulates contributions from the array
	void partial_sum_accumulator(remainder_t remainder, sum_t quotient_contribution, sum_t partial_sum[N]);

	void multiplier(sum_t partial_sum[N], float partial_sum_scale[N]);

	// Partial Sums Generation Unit: Orchestrates sorting and accumulation
	void partial_sums_generation_unit(LNS<B, Q, R, Gamma> inputs[N], float partial_sum_results[N]);

	// Addition Unit: Sums up the partial sums
	void addition_unit(float partial_sum_accumulator_out[N], float &final_sum);

	// Conversion: Convert floating-point result back to LNS format
	void convertback(float sum, LNS<B, Q, R, Gamma> &final_sum);

	// Main adder function
	void adder(LNS<B, Q, R, Gamma> inputs[N], LNS<B, Q, R, Gamma> &final_sum);


}

#endif
