#include "stdint.h"

uint64_t naive_countOnes(uint64_t c) {
    uint64_t count = 0;
    while (c) {
        count += c & 1;
        c = c >> 1;
    }
    return count;
}

uint64_t naive_popcount(uint64_t c) {
    return __builtin_popcountll(c);
}

uint64_t countOnes(uint64_t* buffer, int size) {
    uint64_t count = 0;
    for (int i = 0; i < size; i++) {
        //count += naive_countOnes(buffer[i]);
        count += naive_popcount(buffer[i]);
    }
    return count;
}

