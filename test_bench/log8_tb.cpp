#include "../src/multiplier.cpp"

// Testbench for the Log8 struct
void lns_example() {
// Define base factor Gamma, bit-width B, and bit-widths for quotient and remainder
    constexpr int B = 7;
    constexpr int Q = 4;  // Bit-width for quotient
    constexpr int R = 3;  // Bit-width for remainder
    constexpr int Gamma = 8;

    // Create LNS numbers
    LNS<B, Q, R, Gamma> lns1 = LNS<B, Q, R, Gamma>::from_float(3.5);
    LNS<B, Q, R, Gamma> lns2 = LNS<B, Q, R, Gamma>::from_float(-2.0);

    // Print LNS numbers
    printf("LNS1: ");
    lns1.print();
    printf("LNS2: ");
    lns2.print();

    // Perform operations
    // LNS<B, Q, R, Gamma> sum = lns1 + lns2;
    LNS<B, Q, R, Gamma> product = lns1 * lns2;

    // // Print results
    // printf("Sum: ");
    // sum.print();
    printf("Product: ");
    product.print();

}

int main() {
    
    lns_example();

    return 0;
}