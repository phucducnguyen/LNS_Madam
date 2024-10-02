#include "../src/mac.h"

// int main() {
    
//     // input_a = np.array([1.5, 2.5, 3.5, 4.5])  # Input A values
//     // input_b = np.array([2.5, 3.5, 4.5, 5.5])  # Input B values
    
    LNS<B, Q, R, Gamma> input_a[4] = {LNS<B, Q, R, Gamma>(0, 1, 6), 
                                        LNS<B, Q, R, Gamma>(0, 3, 0),
                                        LNS<B, Q, R, Gamma>(0, 2, 3),
                                        // LNS<B, Q, R, Gamma>(0, 0, 4),
                                        // LNS<B, Q, R, Gamma>(0, 0, 5),
                                        // LNS<B, Q, R, Gamma>(0, 3, 2),
                                        // LNS<B, Q, R, Gamma>(0, 1, 3),
                                        // LNS<B, Q, R, Gamma>(0, 0, 7),
                                        // LNS<B, Q, R, Gamma>(0, 2, 6),
                                        // LNS<B, Q, R, Gamma>(0, 2, 0),
                                        // LNS<B, Q, R, Gamma>(0, 3, 1),
                                        // LNS<B, Q, R, Gamma>(0, 1, 1),
                                        // LNS<B, Q, R, Gamma>(0, 2, 3),
                                        // LNS<B, Q, R, Gamma>(0, 0, 7),
                                        // LNS<B, Q, R, Gamma>(0, 1, 2),
                                        LNS<B, Q, R, Gamma>(0, 1, 5)}; // Log8(0, 2, 1)
    
    LNS<B, Q, R, Gamma> input_b[4] = {LNS<B, Q, R, Gamma>(0, 2, 2),
                                        LNS<B, Q, R, Gamma>(0, 3, 0),
                                        LNS<B, Q, R, Gamma>(0, 0,7),
                                        // LNS<B, Q, R, Gamma>(0, 1, 6),
                                        // LNS<B, Q, R, Gamma>(0, 1, 2),
                                        // LNS<B, Q, R, Gamma>(0, 2, 4),
                                        // LNS<B, Q, R, Gamma>(0, 3, 2),
                                        // LNS<B, Q, R, Gamma>(0, 2, 1),
                                        // LNS<B, Q, R, Gamma>(0, 3, 0),
                                        // LNS<B, Q, R, Gamma>(0, 1, 6),
                                        // LNS<B, Q, R, Gamma>(0, 2, 6),
                                        // LNS<B, Q, R, Gamma>(0, 2, 7),
                                        // LNS<B, Q, R, Gamma>(0, 1, 6),
                                        // LNS<B, Q, R, Gamma>(0, 2, 3),
                                        // LNS<B, Q, R, Gamma>(0, 0, 4),
                                        LNS<B, Q, R, Gamma>(0, 2, 5)};// Log8(0, 2, 3)   

//     LNS<B, Q, R, Gamma> result = LNS<B, Q, R, Gamma>();
    
//     mac(input_a, input_b, result);

//     std::cout << "final_sum(" << result.sign << "," << result.exponent << ")" << std::endl;
//     std::cout << "final_sum(" << result.sign << "," << result.quotient << "," << result.remainder << ")" << std::endl;
//     std::cout << "float_final_sum(" << result.to_float() << ")" << std::endl;
//     std::cout << "All tests completed." << std::endl;
    

//     return 0;
// }

int main() {

    // Define input_a and input_b as 3x3 matrices
    LNS<B, Q, R, Gamma> input_a[N][N] = {
        { LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(0, 3, 0), LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(0, 0, 4) },
        { LNS<B, Q, R, Gamma>(0, 0, 5), LNS<B, Q, R, Gamma>(0, 3, 2), LNS<B, Q, R, Gamma>(0, 1, 3), LNS<B, Q, R, Gamma>(0, 0, 7) },
        { LNS<B, Q, R, Gamma>(0, 2, 6), LNS<B, Q, R, Gamma>(0, 2, 0), LNS<B, Q, R, Gamma>(0, 3, 1), LNS<B, Q, R, Gamma>(0, 1, 1) },
        { LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(0, 0, 7), LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 1, 5) }
    };

    LNS<B, Q, R, Gamma> input_b[N][N] = {
        { LNS<B, Q, R, Gamma>(0, 2, 2), LNS<B, Q, R, Gamma>(0, 3, 0), LNS<B, Q, R, Gamma>(0, 0,7), LNS<B, Q, R, Gamma>(0, 1, 6)},
        { LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 2, 4), LNS<B, Q, R, Gamma>(0, 3, 2),LNS<B, Q, R, Gamma>(0, 2, 1)},
        { LNS<B, Q, R, Gamma>(0, 3, 0), LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(0, 2, 6), LNS<B, Q, R, Gamma>(0, 2, 7)},
        { LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(0, 0, 4), LNS<B, Q, R, Gamma>(0, 2, 5)}
    };

    LNS<B, Q, R, Gamma> result[N][N];

    // Perform matrix multiplication using the mac function
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            LNS<B, Q, R, Gamma> temp_result;
            temp_result = LNS<B, Q, R, Gamma>(); // Initialize to zero

            // Extract the i-th row from input_a and the j-th column from input_b
            LNS<B, Q, R, Gamma> row_a[N];
            LNS<B, Q, R, Gamma> col_b[N];

            for (int k = 0; k < N; k++) {
                row_a[k] = input_a[i][k];
                col_b[k] = input_b[k][j];
            }

            // Use the mac function for the i-th row and j-th column multiplication
            mac(row_a, col_b, temp_result);
            std::cout << "temp_result[" << i << "][" << j << "] = " << temp_result[i][j].to_float() << std::endl;        
            result[i][j] = temp_result; // Store the result
        }
    }

    // Output the result matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << "result[" << i << "][" << j << "] = " << result[i][j].to_float() << std::endl;
            std::cout << "result(" << result[i][j].sign << "," << result[i][j].quotient << "," << result[i][j].remainder << ")" << std::endl;
        }
    }

    std::cout << "All tests completed." << std::endl;
    return 0;
}

// Testbench for mac_nxn
// int main() {
//     // Define input arrays and result
//         // Define input_a and input_b as 3x3 matrices
//     // LNS<B, Q, R, Gamma> array_input_a[N][N] = {
//     //     { LNS<B, Q, R, Gamma>(0, 0, 4), LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 1, 6) },
//     //     { LNS<B, Q, R, Gamma>(0, 2, 1), LNS<B, Q, R, Gamma>(0, 1, 4), LNS<B, Q, R, Gamma>(0, 2, 5) },
//     //     { LNS<B, Q, R, Gamma>(1, 2, 2), LNS<B, Q, R, Gamma>(1, 3, 4), LNS<B, Q, R, Gamma>(0, 2, 1) }
//     // };

//     // LNS<B, Q, R, Gamma> array_input_b[N][N] = {
//     //     { LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(0, 2, 1) },
//     //     { LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(1, 4, 2), LNS<B, Q, R, Gamma>(0, 5, 1) },
//     //     { LNS<B, Q, R, Gamma>(0, 2, 0), LNS<B, Q, R, Gamma>(1, 3, 0), LNS<B, Q, R, Gamma>(0, 2, 3) }
//     // };

//     LNS<B, Q, R, Gamma> array_input_a[N][N] = {
//         { LNS<B, Q, R, Gamma>(0, 0, 4), LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(1, 2, 5),LNS<B, Q, R, Gamma>(0, 4, 0) },
//         { LNS<B, Q, R, Gamma>(0, 2, 1), LNS<B, Q, R, Gamma>(0, 1, 4), LNS<B, Q, R, Gamma>(0, 2, 5), LNS<B, Q, R, Gamma>(1, 5, 1),LNS<B, Q, R, Gamma>(0, 1, 1) },
//         { LNS<B, Q, R, Gamma>(1, 2, 2), LNS<B, Q, R, Gamma>(1, 3, 4), LNS<B, Q, R, Gamma>(0, 2, 1), LNS<B, Q, R, Gamma>(0, 4, 2),LNS<B, Q, R, Gamma>(1, 1, 0) },
//         { LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 1, 5), LNS<B, Q, R, Gamma>(0, 5, 6), LNS<B, Q, R, Gamma>(1, 3, 7),LNS<B, Q, R, Gamma>(1, 0, 7) },
//         { LNS<B, Q, R, Gamma>(0, 5, 7), LNS<B, Q, R, Gamma>(1, 0, 7), LNS<B, Q, R, Gamma>(0, 1, 3), LNS<B, Q, R, Gamma>(1, 1, 7),LNS<B, Q, R, Gamma>(1, 4, 7) }
//     };

//     LNS<B, Q, R, Gamma> array_input_b[N][N] = {
//         { LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(0, 2, 1), LNS<B, Q, R, Gamma>(0, 1, 1),LNS<B, Q, R, Gamma>(1, 5, 1) },
//         { LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(1, 4, 2), LNS<B, Q, R, Gamma>(0, 5, 1), LNS<B, Q, R, Gamma>(1, 4, 4),LNS<B, Q, R, Gamma>(0, 3, 0) },
//         { LNS<B, Q, R, Gamma>(0, 2, 0), LNS<B, Q, R, Gamma>(1, 3, 0), LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(0, 2, 1),LNS<B, Q, R, Gamma>(0, 2, 3) },
//         { LNS<B, Q, R, Gamma>(1, 1, 3), LNS<B, Q, R, Gamma>(0, 4, 1), LNS<B, Q, R, Gamma>(1, 6, 5), LNS<B, Q, R, Gamma>(0, 3, 1),LNS<B, Q, R, Gamma>(1, 1, 2) },
//         { LNS<B, Q, R, Gamma>(1, 4, 0), LNS<B, Q, R, Gamma>(1, 5, 3), LNS<B, Q, R, Gamma>(0, 3, 1), LNS<B, Q, R, Gamma>(0, 3, 6),LNS<B, Q, R, Gamma>(0, 3, 4) }
//     };
    
//     LNS<B, Q, R, Gamma> result[N][N];  // Output matrix

//     // Call mac_nxn
//     mac_nxn(array_input_a, array_input_b, result);

//     // Print the result matrix
//     std::cout << "Result of MAC NxN operation: \n";
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             std::cout << result[i][j].to_float() << " "; // Assuming to_float() method for printing LNS values
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }