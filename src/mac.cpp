
#include "mac.h"

void mac(LNS<B, Q, R, Gamma> array_input_a[N], LNS<B, Q, R, Gamma> array_input_b[N], LNS<B, Q, R, Gamma> &result){
    
    LNS<B, Q, R, Gamma> multiplier_result[N];

    for (int i =0; i < N; i++){
#pragma HLS UNROLL
    multiply(array_input_a[i], array_input_b[i], multiplier_result[i]);
    
    // std::cout << "multiplier_result(" << multiplier_result[i].sign << "," << multiplier_result[i].exponent << ")" << std::endl;
    std::cout << "multiplier_result(" << multiplier_result[i].sign << "," << multiplier_result[i].quotient << "," << multiplier_result[i].remainder <<")" << std::endl;

    // adder(multiplier_result, remainders, result);
   } 

    // quotient_t quotients[N] = {0, 1, 2, 3, 0, 1, 2, 3};
    // remainder_t remainders[N] = {0, 1, 2, 3, 4, 5, 6, 7};
    
    // // Declare the final sum in LNS format
    // LNS<B, Q, R, Gamma> final_sum;

    // // Call the adder function
    // adder(quotients, remainders, final_sum);



    // std::cout << "final_sum(" << final_sum.sign << "," << final_sum.exponent << ")" << std::endl;

    // std::cout << "All tests completed." << std::endl;

}