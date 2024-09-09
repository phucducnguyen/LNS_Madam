// #include "/home/ndp/LNSMadam_HLS/src/mul/mul_unit.h"
#include "../src/add/add_unit.h"

void test_adder() {
    // Input vectors for testing
    
    LNS<B, Q, R, Gamma> input[4] = {LNS<B, Q, R, Gamma>(0,1,6), // Log8(0, 0, 4)
                                    LNS<B, Q, R, Gamma>(0,3,0), // Log8(0, 1, 2)
                                    LNS<B, Q, R, Gamma>(0,3,7), // Log8(0, 1, 6)
                                    LNS<B, Q, R, Gamma>(0,4,4) }; // Log8(0, 2, 1)
    // Declare the final sum in LNS format
    LNS<B, Q, R, Gamma> final_sum;

    // Call the adder function
    adder(input, final_sum);

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