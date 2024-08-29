#ifndef LNS_DATATYPE_H
#define LNS_DATATYPE_H

#include <hls_math.h>
#include <hls_stream.h>
#include <ap_int.h>
#include <cstdio>
#include <iostream>

// Define base factor Gamma, bit-width B, and bit-widths for quotient and remainder
constexpr int B = 7;
constexpr int Q = 4;  // Bit-width for quotient
constexpr int R = 3;  // Bit-width for remainder
constexpr int Gamma = 8;


// Define the LNS data type using a struct
template<int B, int Q, int R, int Gamma>
struct LNS {
    // Data members
    ap_uint<1> sign;       // Sign bit (1-bit)
    ap_uint<B> exponent;   // Full exponent
    ap_uint<Q> quotient;   // Quotient part of the exponent
    ap_uint<R> remainder;  // Remainder part of the exponent

    // Default constructor
    LNS() : sign(0), exponent(0), quotient(0), remainder(0) {}

    // Constructor with parameters
    LNS(ap_uint<1> s, ap_uint<B> exp) : sign(s), exponent(exp){
        quotient = ap_uint<Q>(hls::floor(exp / Gamma));
        remainder = ap_uint<R>(exp - (quotient * Gamma))  ;               
    }
    LNS(ap_uint<1> s, ap_uint<Q> q, ap_uint<R> r) : sign(s), quotient(q), remainder(r) {
        exponent = q * Gamma  + r;
    }    
    LNS(ap_uint<1> s, ap_uint<B> exp, ap_uint<Q> q, ap_uint<R> r) : sign(s), exponent(exp), quotient(q), remainder(r) {}

    // Conversion from a floating-point number to LNS format
    // Optimized conversion from a floating-point number to LNS format
    static LNS from_float(float value) {
        // Handle zero case
        if (value == 0.0f) {
            return LNS(0, 0);  // Zero case
        }
        // Extract sign
        ap_uint<1> s = value < 0 ? 1 : 0;

        // Use integer approximation to calculate exponent
        float abs_value = hls::fabs(value);
        ap_uint<Q> q = (hls::floor(hls::log2(abs_value)));
        // Ensure the exponent fits within the bit-width B
        ap_uint<R> r = (Gamma * (hls::log2(abs_value) - q));

        // Create LNS object with computed values
        return LNS(s, q, r);
    }

    // Convert LNS to a float (for simulation purposes)
    float to_float() const {
        float value = hls::pow(2, quotient + (remainder/Gamma));
        return sign.to_int() ? -value : value;
    }

    // Arithmetic operations
    LNS operator*(const LNS& other) const {
        // Implement multiplication of LNS numbers
        ap_uint<1> result_sign = sign ^ other.sign;  // XOR to determine the sign
        ap_uint<B> result_exp = exponent + other.exponent;
        return LNS(result_sign, result_exp);
    }

    // Print function to display LNS representation
    void print() const {
        printf("LNS Representation: ");
        printf("Sign: %d, ", sign.to_int());
        printf("Exponent: (Quotient: %d, Remainder: %d), ", quotient.to_int(), remainder.to_int());
        printf("Full Exponent: %d\n", exponent.to_int());
    }
};


#endif // LNS_DATATYPE_H