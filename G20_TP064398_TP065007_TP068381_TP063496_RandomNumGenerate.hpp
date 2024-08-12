#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class RandomNumberGenerator {
private:
    static const int MAX_SIZE = 300; // maximum possible unique numbers in the range [0, 299]
    int generatedNumbers[MAX_SIZE];
    int count;

public:
    RandomNumberGenerator() {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < MAX_SIZE; ++i) {
            generatedNumbers[i] = -1; // Initialize with an invalid number
        }
        count = 0;
    }

    int generate() {
        if (count >= MAX_SIZE) {
            cerr << "Error: All possible unique numbers have been generated." << endl;
            exit(1); // Exit the program if all unique numbers are used
        }

        int number;
        bool isUnique;
        do {
            number = rand() % 300;
            isUnique = true;
            for (int i = 0; i < count; ++i) {
                if (generatedNumbers[i] == number) {
                    isUnique = false;
                    break;
                }
            }
        } while (!isUnique);

        generatedNumbers[count++] = number;
        return number;
    }
};