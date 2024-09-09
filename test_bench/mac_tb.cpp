#include "../src/mac.h"

int main() {
    
    // input_a = np.array([1.5, 2.5, 3.5, 4.5])  # Input A values
    // input_b = np.array([2.5, 3.5, 4.5, 5.5])  # Input B values
    
    LNS<B, Q, R, Gamma> input_a[4] = {LNS<B, Q, R, Gamma>(0, 0, 4), // Log8(0, 0, 4)
                                    LNS<B, Q, R, Gamma>(0, 1, 2), // Log8(0, 1, 2)
                                    LNS<B, Q, R, Gamma>(0, 1, 6), // Log8(0, 1, 6)
                                    LNS<B, Q, R, Gamma>(0, 2, 1) }; // Log8(0, 2, 1)
    
    LNS<B, Q, R, Gamma> input_b[4] = {LNS<B, Q, R, Gamma>(0, 1, 2), // Log8(0, 1, 2)
                                    LNS<B, Q, R, Gamma>(0, 1, 6), // Log8(0, 1, 6)
                                    LNS<B, Q, R, Gamma>(0, 2, 1), // Log8(0, 2, 1)
                                    LNS<B, Q, R, Gamma>(0, 2, 3)   }; // Log8(0, 2, 3)   

    LNS<B, Q, R, Gamma> result = LNS<B, Q, R, Gamma>();
    
    mac(input_a, input_b, result);
    

    return 0;
}