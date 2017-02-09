#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdint.h>
#include "hwtimer.h"

using namespace::std;

extern int countOnes(uint64_t* buffer, int size);

int main (int argc, char** argv) {
    char* fileName;
    
    hwtimer_t timer;
    initTimer(&timer);

    if (argc != 2) {
        cerr<<"Usage: ./bitCount [fileName]"<<endl;
        exit(0);
    } else {
        fileName = argv[1];
    }

    ifstream input(fileName, std::ifstream::binary);
    if (input.is_open()) {
        input.seekg(0, input.end);
        int size = input.tellg();
        input.seekg(0, input.beg);

        int rsize = (size + 7) / 8;
        uint64_t* buffer = new uint64_t[rsize];

        startTimer(&timer);
        input.read((char*)buffer, size);
        stopTimer(&timer);
        cout << "Read from memory time: " << getTimerNs(&timer) << " ns\n";

        if (input)
        {
            
            startTimer(&timer);
            int nOnes = countOnes(buffer, rsize);
            stopTimer(&timer);
            cout << "Computation time: " << getTimerNs(&timer) << " ns\n";
            cout << "Number of ones: " << nOnes << endl;
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
