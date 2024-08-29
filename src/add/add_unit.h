#include "../LNS_datatype.h" // Ensure this header file includes LNS class definition

#define N 8 // Number of accumulators

typedef ap_uint<4> quotient_t;
typedef ap_uint<3> remainder_t;
typedef ap_uint<16> sum_t;

extern "C" {
	// void add(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result);
	// Sorting Unit
	void sorting_unit(quotient_t quotient, remainder_t remainder, hls::stream<sum_t> partial_sums[N]);

	// Partial Sums Accumulator
	void partial_sum_accumulator(hls::stream<sum_t> partial_sums[N], sum_t &result_sum);

	// Partial Sums Generation Unit
	void add(quotient_t quotients[N], remainder_t remainders[N], sum_t &final_sum);
	//partial_sums_generation_unit
	}