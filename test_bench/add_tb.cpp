// #include "/home/ndp/LNSMadam_HLS/src/mul/mul_unit.h"
#include "../src/add/add_unit.h"

int main() {
    
    // test_multiplier<B, Q, R, Gamma>();

    // Create LNS numbers
    LNS<B, Q, R, Gamma> a = LNS<B, Q, R, Gamma>::from_float(3.5);
    LNS<B, Q, R, Gamma> b = LNS<B, Q, R, Gamma>::from_float(-2.0);
    
    LNS<B, Q, R, Gamma> result; // Output result

    add(a, b, result);
    std::cout << "Test Case 1: ";
    std::cout << "a(" << a.sign << "," << a.exponent << ") ";
    std::cout << "b(" << b.sign << "," << b.exponent << ") ";
    std::cout << "result(" << result.sign << "," << result.exponent << ")" << std::endl;

    std::cout << "All tests completed." << std::endl;

    return 0;
}