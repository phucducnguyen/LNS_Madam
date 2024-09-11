// #include "/home/ndp/LNSMadam_HLS/src/mul/mul_unit.h"
#include "../src/add/add_unit.h"

int main() {
    // Run the testbench
    // test_adder();

    LNS<B, Q, R, Gamma> input[4] = {LNS<B, Q, R, Gamma>(0,1,6), // Log8(0, 0, 4)
                                    LNS<B, Q, R, Gamma>(0,3,0), // Log8(0, 1, 2)
                                    LNS<B, Q, R, Gamma>(0,3,7), // Log8(0, 1, 6)
                                    LNS<B, Q, R, Gamma>(0,4,4) }; // Log8(0, 2, 1)
    // Declare the final sum in LNS format
    LNS<B, Q, R, Gamma> final_sum;

    // Call the adder function
    adder(input, final_sum);

    // float float_final_sum = final_sum.to_float();

    std::cout << "final_sum(" << final_sum.sign << "," << final_sum.exponent << ")" << std::endl;
    std::cout << "final_sum(" << final_sum.sign << "," << final_sum.quotient << "," << final_sum.remainder << ")" << std::endl;
    std::cout << "float_final_sum(" << final_sum.to_float() << ")" << std::endl;
    std::cout << "All tests completed." << std::endl;
    return 0;
}