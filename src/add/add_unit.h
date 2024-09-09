#include "../LNS_datatype.h" // Ensure this header file includes LNS class definition

#define N 8 // Number of accumulators

typedef ap_uint<4> quotient_t;
typedef ap_uint<3> remainder_t;
typedef ap_uint<16> sum_t;

extern "C" {
	// void add(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result);
	// Function to initialize the lookup table
	void initialize_lut();
	
	// Sorting Unit: Outputs contributions based on quotient and remainder
	void sorting_unit(quotient_t quotients[N], remainder_t remainders[N], sum_t out_sums[N]);

	// Partial Sums Accumulator: Accumulates contributions from the array
	void partial_sum_accumulator(float lut[N], sum_t input_sums[N], float partial_sum[N]);

	// Partial Sums Generation Unit: Orchestrates sorting and accumulation
	void partial_sums_generation_unit(quotient_t quotients[N], remainder_t remainders[N], float partial_sum_results[N]);

	// Addition Unit: Sums up the partial sums
	void addition_unit(float partial_sum_accumulator_out[N], float &final_sum);

	// Conversion: Convert floating-point result back to LNS format
	template<int B, int Q, int R, int Gamma>
	void convertback(float sum, LNS<B, Q, R, Gamma> &final_sum);

	// Main adder function
	//template<int B, int Q, int R, int Gamma>
	void adder(quotient_t quotients[N], remainder_t remainders[N], LNS<B, Q, R, Gamma> &final_sum);


}
