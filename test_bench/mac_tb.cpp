#include "../src/mac.h"

// int main() {
    
//     // input_a = np.array([1.5, 2.5, 3.5, 4.5])  # Input A values
//     // input_b = np.array([2.5, 3.5, 4.5, 5.5])  # Input B values
    
    // LNS<B, Q, R, Gamma> input_a[4] = {LNS<B, Q, R, Gamma>(0, 1, 6), 
    //                                     LNS<B, Q, R, Gamma>(0, 3, 0),
    //                                     LNS<B, Q, R, Gamma>(0, 2, 3),
    //                                     // LNS<B, Q, R, Gamma>(0, 0, 4),
    //                                     // LNS<B, Q, R, Gamma>(0, 0, 5),
    //                                     // LNS<B, Q, R, Gamma>(0, 3, 2),
    //                                     // LNS<B, Q, R, Gamma>(0, 1, 3),
    //                                     // LNS<B, Q, R, Gamma>(0, 0, 7),
    //                                     // LNS<B, Q, R, Gamma>(0, 2, 6),
    //                                     // LNS<B, Q, R, Gamma>(0, 2, 0),
    //                                     // LNS<B, Q, R, Gamma>(0, 3, 1),
    //                                     // LNS<B, Q, R, Gamma>(0, 1, 1),
    //                                     // LNS<B, Q, R, Gamma>(0, 2, 3),
    //                                     // LNS<B, Q, R, Gamma>(0, 0, 7),
    //                                     // LNS<B, Q, R, Gamma>(0, 1, 2),
    //                                     LNS<B, Q, R, Gamma>(0, 1, 5)}; // Log8(0, 2, 1)
    
    // LNS<B, Q, R, Gamma> input_b[4] = {LNS<B, Q, R, Gamma>(0, 2, 2),
    //                                     LNS<B, Q, R, Gamma>(0, 3, 0),
    //                                     LNS<B, Q, R, Gamma>(0, 0,7),
    //                                     // LNS<B, Q, R, Gamma>(0, 1, 6),
    //                                     // LNS<B, Q, R, Gamma>(0, 1, 2),
    //                                     // LNS<B, Q, R, Gamma>(0, 2, 4),
    //                                     // LNS<B, Q, R, Gamma>(0, 3, 2),
    //                                     // LNS<B, Q, R, Gamma>(0, 2, 1),
    //                                     // LNS<B, Q, R, Gamma>(0, 3, 0),
    //                                     // LNS<B, Q, R, Gamma>(0, 1, 6),
    //                                     // LNS<B, Q, R, Gamma>(0, 2, 6),
    //                                     // LNS<B, Q, R, Gamma>(0, 2, 7),
    //                                     // LNS<B, Q, R, Gamma>(0, 1, 6),
    //                                     // LNS<B, Q, R, Gamma>(0, 2, 3),
    //                                     // LNS<B, Q, R, Gamma>(0, 0, 4),
    //                                     LNS<B, Q, R, Gamma>(0, 2, 5)};// Log8(0, 2, 3)   

//     LNS<B, Q, R, Gamma> result = LNS<B, Q, R, Gamma>();
    
//     mac(input_a, input_b, result);

//     std::cout << "final_sum(" << result.sign << "," << result.exponent << ")" << std::endl;
//     std::cout << "final_sum(" << result.sign << "," << result.quotient << "," << result.remainder << ")" << std::endl;
//     std::cout << "float_final_sum(" << result.to_float() << ")" << std::endl;
//     std::cout << "All tests completed." << std::endl;
    

//     return 0;
// }

// int main() {

//     // Define input_a and input_b as nxn matrices
//     LNS<B, Q, R, Gamma> input_a[N][N] = {
//         { LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(0, 3, 0), LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(0, 0, 4) },
//         { LNS<B, Q, R, Gamma>(0, 0, 5), LNS<B, Q, R, Gamma>(0, 3, 2), LNS<B, Q, R, Gamma>(0, 1, 3), LNS<B, Q, R, Gamma>(0, 0, 7) },
//         { LNS<B, Q, R, Gamma>(0, 2, 6), LNS<B, Q, R, Gamma>(0, 2, 0), LNS<B, Q, R, Gamma>(0, 3, 1), LNS<B, Q, R, Gamma>(0, 1, 1) },
//         { LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(0, 0, 7), LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 1, 5) }
//     };

//     LNS<B, Q, R, Gamma> input_b[N][N] = {
//         { LNS<B, Q, R, Gamma>(0, 2, 2), LNS<B, Q, R, Gamma>(0, 3, 0), LNS<B, Q, R, Gamma>(0, 0,7), LNS<B, Q, R, Gamma>(0, 1, 6)},
//         { LNS<B, Q, R, Gamma>(0, 1, 2), LNS<B, Q, R, Gamma>(0, 2, 4), LNS<B, Q, R, Gamma>(0, 3, 2),LNS<B, Q, R, Gamma>(0, 2, 1)},
//         { LNS<B, Q, R, Gamma>(0, 3, 0), LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(0, 2, 6), LNS<B, Q, R, Gamma>(0, 2, 7)},
//         { LNS<B, Q, R, Gamma>(0, 1, 6), LNS<B, Q, R, Gamma>(0, 2, 3), LNS<B, Q, R, Gamma>(0, 0, 4), LNS<B, Q, R, Gamma>(0, 2, 5)}
//     };

//     LNS<B, Q, R, Gamma> result[N][N];

//     // Perform matrix multiplication using the mac function
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             LNS<B, Q, R, Gamma> temp_result;
//             temp_result = LNS<B, Q, R, Gamma>(); // Initialize to zero

//             // Extract the i-th row from input_a and the j-th column from input_b
//             LNS<B, Q, R, Gamma> row_a[N];
//             LNS<B, Q, R, Gamma> col_b[N];

//             for (int k = 0; k < N; k++) {
//                 row_a[k] = input_a[i][k];
//                 col_b[k] = input_b[k][j];
//             }

//             // Use the mac function for the i-th row and j-th column multiplication
//             mac_array(row_a, col_b, temp_result);
//             std::cout << "temp_result[" << i << "][" << j << "] = " << temp_result[i][j].to_float() << std::endl;        
//             result[i][j] = temp_result; // Store the result
//         }
//     }

//     // Output the result matrix
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             std::cout << "result[" << i << "][" << j << "] = " << result[i][j].to_float() << std::endl;
//             std::cout << "result(" << result[i][j].sign << "," << result[i][j].quotient << "," << result[i][j].remainder << ")" << std::endl;
//         }
//     }

//     std::cout << "All tests completed." << std::endl;
//     return 0;
// }

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




/////////////////////////// Quantization Error ////////////////////////////////

int main() {
    double matrixA[8][8] = {
    {1.123, 5.345, 9.001, 2.567},
    {3.234, 8.789, 7.456, 4.876},
    {6.112, 2.912, 5.654, 3.234},
    {4.201, 10.321, 2.678, 6.432},
    {1.1234, 1.5678, 1.9876, 1.2345},
    {1.3456, 1.6789, 1.4567, 1.8901},
    {1.2345, 1.5432, 1.8765, 1.6789},
    {1.7654, 1.8901, 1.2345, 1.4567}
    };
    double matrixB[8][8] = {
    {8.512, 3.834, 10.000, 7.947},
    {2.341, 9.256, 5.634, 1.159},
    {10.198, 4.432, 1.907, 6.765},
    {3.582, 7.213, 9.389, 2.876},
    {1.2345, 1.8765, 1.5432, 1.6789},
    {1.6789, 1.3456, 1.7890, 1.2345},
    {1.8901, 1.1234, 1.4567, 1.5678},
    {1.4567, 1.2345, 1.8901, 1.6789}
    };
    // // Define input_a and input_b as nxn matrices
    LNS<B, Q, R, Gamma> input_a[N][N] = {};
    LNS<B, Q, R, Gamma> input_b[N][N] = {};
    LNS<B, Q, R, Gamma> result[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            input_a[i][j]= LNS<B, Q, R, Gamma>::from_float(matrixA[i][j]);
            input_b[i][j]= LNS<B, Q, R, Gamma>::from_float(matrixB[i][j]);
        }
    }

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
            mac_array(row_a, col_b, temp_result);


            double expected_value = 0.0; // Compute the expected value based on double precision
            for (int k = 0; k < N; k++) {
                expected_value += matrixA[i][k] * matrixB[k][j];
            }
            double quantized_value = temp_result.to_float();
            double quantization_error = fabs(expected_value - quantized_value);
            double percentage_error = (expected_value != 0) ? (quantization_error / expected_value) * 100 : 0;

            std::cout << "expected_value = " << expected_value << std::endl;
            std::cout << "temp_result = (" << temp_result.sign << "," << temp_result.quotient << "," << temp_result.remainder << ")" << std::endl;
            std::cout << "temp_result[" << i << "][" << j << "] = " << quantized_value 
                << " (expected: " << expected_value 
                << ", error: " << quantization_error 
                << ", percentage error: " << percentage_error << "%)" << std::endl;


            result[i][j] = temp_result; // Store the result
        }
    }

    // // Output the result matrix
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         std::cout << "result[" << i << "][" << j << "] = " << result[i][j].to_float() << std::endl;
    //         std::cout << "result(" << result[i][j].sign << "," << result[i][j].quotient << "," << result[i][j].remainder << ")" << std::endl;
    //     }
    // }

    std::cout << "All tests completed." << std::endl;
    return 0;
}