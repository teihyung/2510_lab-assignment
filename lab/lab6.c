#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


long long signed_min(int bitwidth) {
    long long min = 1LL << (bitwidth - 1);
    return -min;
}

long long signed_max(int bitwidth) {
    long long max = (1LL << (bitwidth - 1)) - 1;
    return max;
}

long long sat_add(long long operand1, long long operand2, int bitwidth) {
    long long max_val = signed_max(bitwidth);
    long long min_val = signed_min(bitwidth);
    long long result = operand1 + operand2;
    int sign_bit = (result >> (bitwidth - 1)) & 0x01;
    int negative_bit = (result >> (bitwidth)) & 0x01;

    if (sign_bit == 1 && negative_bit == 0) {
        return max_val;
    } else if (negative_bit == 1 && sign_bit == 0) {
        return min_val;
    } else {
        return result;
    }
}


long long sat_sub(long long operand1, long long operand2, int bitwidth) {
    long long max_val = signed_max(bitwidth);
    long long min_val = signed_min(bitwidth);
    long long result = operand1 - operand2;

    int sign_bit = (result >> (bitwidth - 1)) & 0x01;
    int negative_bit = (result >> (bitwidth)) & 0x01;
    if (sign_bit == 1 && negative_bit == 0) {
        return max_val;
    } else if (negative_bit == 1 && sign_bit == 0) {
        return min_val;
    } else {
        return result;
    }

}


int main(int argc, char **argv) {

    int BitWidth = atoi(argv[1]);
    if (argc == 2) {
        printf("%d-bit signed integer range\n", BitWidth);
        printf("min: %lld \t0x%016llx\n", signed_min(BitWidth), signed_min(BitWidth));
        printf("max: %lld \t0x%016llx\n", signed_max(BitWidth), signed_max(BitWidth));
    } else {
        int var1 = atoi(argv[2]);
        int var2 = atoi(argv[3]);
        int option = atoi(argv[4]);
        if (option == 0) {
            printf("%lld + %lld = %lld\n", (long long) var1, (long long) var2,
                   sat_add((long long) var1, (long long) var2, BitWidth));
        } else {
            printf("%lld - %lld = %lld\n", (long long) var1, (long long) var2,
                   sat_sub((long long) var1, (long long) var2, BitWidth));
        }
    }



    return 0;
}