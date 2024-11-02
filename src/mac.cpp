
#include "mac.h"

void mac_array(LNS<B, Q, R, Gamma> array_input_a[N], LNS<B, Q, R, Gamma> array_input_b[N], LNS<B, Q, R, Gamma> &result){
    LNS<B, Q, R, Gamma> multiplier_result[N];

    multiply_array(array_input_a, array_input_b, multiplier_result);
    adder(multiplier_result, result);
}

void mac_nxn_array(LNS<B, Q, R, Gamma> array_input_a[N][N], LNS<B, Q, R, Gamma> array_input_b[N][N], LNS<B, Q, R, Gamma> result[N][N]){
// #pragma HLS INLINE off
#pragma HLS PIPELINE
// Use BRAM resource for arrays
#pragma HLS INTERFACE m_axi port=array_input_a offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=array_input_b offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=result offset=slave bundle=gmem
#pragma HLS INTERFACE ap_ctrl_none port=return
    // Extract the i-th row from input_a and the j-th column from input_b
    LNS<B, Q, R, Gamma> row_a[N];
    LNS<B, Q, R, Gamma> col_b[N];
    LNS<B, Q, R, Gamma> temp_result;

    // Perform matrix multiplication using the mac function
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                row_a[k] = array_input_a[i][k];
                col_b[k] = array_input_b[k][j];
            }   
            mac_array(row_a,col_b,temp_result);
            result[i][j] = temp_result;
        }
    }
}

void mac_nxn(LNS<B, Q, R, Gamma> array_input_a[N][N], LNS<B, Q, R, Gamma> array_input_b[N][N], LNS<B, Q, R, Gamma> result[N][N]){
#pragma HLS PIPELINE
#pragma HLS INTERFACE m_axi port=array_input_a offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=array_input_b offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=result offset=slave bundle=gmem
#pragma HLS INTERFACE ap_ctrl_none port=return

    LNS<B, Q, R, Gamma> temp_sum[N]; // Temporary array to hold row sums
    LNS<B, Q, R, Gamma> temp_result; // To store result of adder

    // For each row in the first matrix
    for (int i = 0; i < N; i++) {
        // For each column in the second matrix
        for (int j = 0; j < N; j++) {
            // Reset the temp_sum for this column
            for (int k = 0; k < N; k++) {
                // Perform multiply for each element in the row and column
                LNS<B, Q, R, Gamma> product;
                multiply(array_input_a[i][k], array_input_b[k][j], product);
                temp_sum[k] = product; // Store product in temp_sum
            }

            // Use adder to sum the temp_sum array and add it to temp_result
            adder(temp_sum, temp_result);

            // Store the final sum for this row in the result matrix
            result[i][j] = temp_result; // Assuming we want to store the sum in the first column
        }

    }
}
