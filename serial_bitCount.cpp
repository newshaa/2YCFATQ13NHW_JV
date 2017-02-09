#include "stdint.h"

int naive_countOnes(uint64_t c) {
    int count = 0;
    while (c) {
        count += c & 1;
        c = c >> 1;
    }
    return count;
}

int naive_popcount(uint64_t c) {
    return __builtin_popcountll(c);
}

int countOnes(uint64_t* buffer, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        //count += naive_countOnes(buffer[i]);
        count += naive_popcount(buffer[i]);
    }
    return count;
}

