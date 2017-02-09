#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdint.h>
#include "hwtimer.h"

using namespace::std;

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

int serial_count(uint64_t* buffer, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        //count += naive_countOnes(buffer[i]);
        count += naive_popcount(buffer[i]);
    }
    return count;
}

int parallel_count(uint64_t* buffer, int size) {
    return 0;
}

int main (int argc, char** argv) {
    char* fileName;
    int option;
    
    hwtimer_t timer;
    initTimer(&timer);

    if (argc != 3) {
        cerr<<"Usage: ./bitCount [fileName] [serial=0|parallel=1]"<<endl;
        exit(0);
    } else {
        fileName = argv[1];
        option = atoi(argv[2]);
    }

    ifstream input(fileName, std::ifstream::binary);
    if (input.is_open()) {
        input.seekg(0, input.end);
        int size = input.tellg();
        input.seekg(0, input.beg);

        int rsize = (size + 7) /8;
        uint64_t* buffer = new uint64_t[rsize];

        startTimer(&timer);
        input.read((char*)buffer, size);
        stopTimer(&timer);
        cout<<"Read from memory time: "<<getTimerNs(&timer)<<" ns\n";

        if (input)
        {
            
            int nOnes = 0;
            startTimer(&timer);
            switch (option) {
                case 0: nOnes = serial_count(buffer, rsize); break;
                case 1: nOnes = parallel_count(buffer, rsize); break;
            }
            stopTimer(&timer);
            cout<<"Computation time: "<<getTimerNs(&timer)<<" ns\n";
            cout << "Number of ones: "<<nOnes<<endl;
        }
        else {
            cerr << "File could not be read" << endl;
        }
        input.close();
        delete[] buffer;
    }
    else {
        cout<<"Error opening file"<<endl;
    }
}
