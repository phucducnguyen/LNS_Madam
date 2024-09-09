// #include "/home/ndp/LNSMadam_HLS/src/mul/mul_unit.h"
#include "../src/add/add_unit.h"

void test_adder() {
    // Input vectors for testing
    quotient_t quotients[N] = {0, 1, 2, 3, 0, 1, 2, 3};
    remainder_t remainders[N] = {0, 1, 2, 3, 4, 5, 6, 7};
    
    // Declare the final sum in LNS format
    LNS<B, Q, R, Gamma> final_sum;

    // Call the adder function
    adder<B, Q, R, Gamma>(quotients, remainders, final_sum);

    // // Output the result
    // std::cout << "Final Sum in LNS format: " << final_sum << std::endl;

    // Additional checks can be added here
    // e.g., Compare with expected results and report pass/fail status
}

int main() {
    // Run the testbench
    test_adder();
    return 0;
}