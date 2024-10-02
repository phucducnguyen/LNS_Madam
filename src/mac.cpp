
#include "mac.h"

void mac(LNS<B, Q, R, Gamma> array_input_a[N], LNS<B, Q, R, Gamma> array_input_b[N], LNS<B, Q, R, Gamma> &result){
// #pragma HLS PIPELINE II=1
#pragma HLS DATAFLOW
// #pragma HLS ARRAY_PARTITION variable=array_input_a cyclic factor=P
// #pragma HLS ARRAY_PARTITION variable=array_input_b cyclic factor=P
    LNS<B, Q, R, Gamma> multiplier_result[N];

    multiply(array_input_a, array_input_b, multiplier_result);
    adder(multiplier_result, result);
}

void mac_nxn(LNS<B, Q, R, Gamma> array_input_a[N][N], LNS<B, Q, R, Gamma> array_input_b[N][N], LNS<B, Q, R, Gamma> result[N][N]){
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION variable=array_input_a cyclic factor=P
#pragma HLS ARRAY_PARTITION variable=array_input_b cyclic factor=P
#pragma HLS ARRAY_PARTITION variable=result cyclic factor=P
// #pragma HLS INTERFACE ap_ctrl_hs port=return

    // Extract the i-th row from input_a and the j-th column from input_b
    LNS<B, Q, R, Gamma> row_a[N];
    LNS<B, Q, R, Gamma> col_b[N];

    // Perform matrix multiplication using the mac function
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL factor=2
        for (int j = 0; j < N; j++) {
#pragma HLS UNROLL factor=2
            LNS<B, Q, R, Gamma> temp_result;
            temp_result = LNS<B, Q, R, Gamma>(); // Initialize to zero

            
// #pragma HLS ARRAY_PARTITION variable=row_a cyclic factor=P
// #pragma HLS ARRAY_PARTITION variable=col_b cyclic factor=P

            for (int k = 0; k < N; k++) {
#pragma HLS UNROLL //factor=2
                row_a[k] = array_input_a[i][k];
                col_b[k] = array_input_b[k][j];
            }

            mac(row_a,col_b,temp_result);
            result[i][j] = temp_result;
        }
    }
}
