#include "../LNS_datatype.h" // Ensure this header file includes LNS class definition
extern "C" {
	void add(const LNS<B, Q, R, Gamma>& a, const LNS<B, Q, R, Gamma>& b, LNS<B, Q, R, Gamma>& result);
	}

