#ifndef MUL_UNIT_H
#define MUL_UNIT_H

#include "../LNS_datatype.h" // Ensure this header file includes LNS class definition
extern "C" {
	// void multiply(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result);
    void multiply(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result);
	}

#endif