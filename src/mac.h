// #ifndef MAC_H
// #define MAC_H

// #include "../src/LNS_datatype.h"
#include "../src/add/add_unit.h"
#include "../src/mul/mul_unit.h"


extern "C" {
    void mac(LNS<B, Q, R, Gamma> array_input_a[N], LNS<B, Q, R, Gamma> array_input_b[N], LNS<B, Q, R, Gamma> &result);
    void mac_nxn(LNS<B, Q, R, Gamma> array_input_a[N][N], LNS<B, Q, R, Gamma> array_input_b[N][N], LNS<B, Q, R, Gamma> result[N][N]);
}


// #endif
