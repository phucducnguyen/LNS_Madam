#include "../src/mac.h"

int main() {
    
    // input_a = np.array([1.5, 2.5, 3.5, 4.5])  # Input A values
    // input_b = np.array([2.5, 3.5, 4.5, 5.5])  # Input B values
    
    LNS<B, Q, R, Gamma> input_a[8] = {LNS<B, Q, R, Gamma>(0, 0, 4), // Log8(0, 0, 4)
                                    LNS<B, Q, R, Gamma>(0, 1, 2), // Log8(0, 1, 2)
                                    LNS<B, Q, R, Gamma>(0, 1, 6), // Log8(0, 1, 6)
                                    LNS<B, Q, R, Gamma>(0, 2, 1),
                                    LNS<B, Q, R, Gamma>(0, 1, 4),
                                    LNS<B, Q, R, Gamma>(0, 2, 5),
                                    LNS<B, Q, R, Gamma>(1, 2, 2),
                                    LNS<B, Q, R, Gamma>(1, 3, 4) }; // Log8(0, 2, 1)
    
    LNS<B, Q, R, Gamma> input_b[8] = {LNS<B, Q, R, Gamma>(0, 1, 2), // Log8(0, 1, 2)
                                    LNS<B, Q, R, Gamma>(0, 1, 6), // Log8(0, 1, 6)
                                    LNS<B, Q, R, Gamma>(0, 2, 1), // Log8(0, 2, 1)
                                    LNS<B, Q, R, Gamma>(0, 2, 3),
                                    LNS<B, Q, R, Gamma>(1, 4, 2),
                                    LNS<B, Q, R, Gamma>(0, 5, 1),
                                    LNS<B, Q, R, Gamma>(0, 2, 0),
                                    LNS<B, Q, R, Gamma>(1, 3, 0) }; // Log8(0, 2, 3)   

    LNS<B, Q, R, Gamma> result = LNS<B, Q, R, Gamma>();
    
    mac(input_a, input_b, result);

    std::cout << "final_sum(" << result.sign << "," << result.exponent << ")" << std::endl;
    std::cout << "final_sum(" << result.sign << "," << result.quotient << "," << result.remainder << ")" << std::endl;
    std::cout << "float_final_sum(" << result.to_float() << ")" << std::endl;
    std::cout << "All tests completed." << std::endl;
    

    return 0;
}